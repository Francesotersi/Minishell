/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:43:26 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/13 10:44:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	next_command(t_exec *exec, t_token **token);
static int	invoke_programs(t_exec *exec, int i);

//NOTE - Il main della parte di esecuzione.
//		Utilizzo:
//		Manda il puntatore al primo token, t_data (castato void *), 0.
//		execute(token, (void *)t_data, 0);
//		execute torna sempre 0.
//		QUANDO CHIAMI EXECUTE OGNI FILE APERTO/MEMORIA ALLOCATA DEVE ESSERE
//		LIBERATA, OPPURE INSERITA NELLA STRUTTURA t_data, IN UN PUNTATORE
//		CHE PUNTA ALLA TUA STRUTTURA DATI.
//		Devi avere poi una funzione che libera tutta la tua memoria, cosi
//		che possa chiamarla quando viene lanciato exit.
//
/*REVIEW - execute

//	1)	We declare the exec struct in stack, and assign it to {0}.
	2)	We get some data from main struct:
		-	The address of the environment (char **);
		-	The address of the environment size (int);
		-	The address of the environment last element (int);
		-	The address of the exit code.
	3)	We change the token array, in the following cases:
		CASE			OLD_TOKENS			NEW_TOKENS
		<(...			<, (				-
		(ls)			(, ls, )			ls
		>file			>, file				file

		Then, we index every command block (ls | cat: ls == 0, cat == 1);
	4)	We alloc memory;
	5)	We open all the here docs, and store their fds in a int array;
	6)	Get a 3D matrix, that stores the argv of each command.
		Example: echo Hello! | cat > file1.txt
		matrix = {{"echo", "Hello!", NULL}, {"cat", "file1.txt", NULL}}
	7)	We get the path of every command. Builtin are not converted.
		matrix = {{"echo", "Hello!", NULL}, {"/bin/cat", "file1.txt", NULL}}
	8)	While there are command blocks in parenthesis, we execute them;
	9)	Now, we iterate every command in execute_loop;
	10)	We free only the memory of execution.
*/
int	execute(t_token *token, void *data, int debug)
{
	t_exec	exec;

	p_tok(token);
	exec = (t_exec){0};
	get_main_struct_data(&exec, data, debug);
	merge_tokens(token, debug);
	alloc_memory(&exec, token, count_commands(&exec, token));
	prepare_here_docs(&exec, token);
	get_commands_data(&exec, token);
	get_paths_data(&exec, token);
	while (token->prior > 0)
	{
		manage_parenthesis(&exec, &token, 0);
		if (exec.pipe_fds[0])
		{
			dup_and_reset(&exec.pipe_fds[0], 0);
		}
	}
	if (token->content)
		execute_loop(token, &exec);
	wait_everyone(&exec);
	p_end(&exec);
	free_memory(&exec);
	return (0);
}

/*REVIEW - execute_loop

//	1)	We update the layer, the current command, we check if in the
		current command block there are at least one pipe;
	2)	We iterate while there are token with a valid content;
	3)	We set the exit status at 0, and we restore STDOUT;
	4)	In get_filedata, we check for pipe/file, and we alter STDIN/OUT;
	5)	If get_filedata does not fail (bad files given in prompt),
		we invoke the program in a child.
		Else, exit code is set to 1;
	6)	We close temp files (here_doc and proc sub fds, like <(ls));
	7)	If there is a STDIN pipe opened, we dup it;
	8)	We go to the next command block;
	9)	The same as 7. In next_command weird things happens :);
	10)	We update the curr command index;
	11)	We wait every children. If the layer is not 0, we exit from the
		process.
*/
int	execute_loop(t_token *token, t_exec *exec)
{
	exec->prior_layer = token->prior;
	exec->curr_cmd = token->cmd_num;
	exec->at_least_one_pipe = detect_pipe(token, _NO, token->prior);
	while (token->content)
	{
		*exec->exit_code = 0;
		dup2(exec->stdout_fd, 1);
		if (get_file_data(exec, token, _YES) == 0)
			invoke_programs(exec, exec->curr_cmd);
		else
			*exec->exit_code = 1;
		close_temp_files(exec);
		if (exec->pipe_fds[0])
			dup_and_reset(&exec->pipe_fds[0], 0);
		if (next_command(exec, &token))
			break ;
		if (exec->pipe_fds[0])
			dup_and_reset(&exec->pipe_fds[0], 0);
		exec->curr_cmd = token->cmd_num;
	}
	wait_everyone(exec);
	if (exec->prior_layer != 0)
		exit_process(exec);
	return (0);
}

/*REVIEW - execute

*/
static int	next_command(t_exec *exec, t_token **token)
{
	while (exec->prior_layer <= (*token)->prior && \
		!(exec->prior_layer == (*token)->prior && is_exec_sep((*token)->type)))
		++(*token);
	if ((*token)->type == AND || (*token)->type == OR)
	{
		exec->curr_cmd += 1;
		wait_everyone(exec);
		goto_valid_block(exec, token);
		exec->at_least_one_pipe = detect_pipe(*token, _NO, (*token)->prior);
	}
	exec->curr_cmd = (*token)->cmd_num;
	if (!(*token)->content || exec->prior_layer > (*token)->prior)
		return (1);
	++(*token);
	exec->curr_cmd = (*token)->cmd_num;
	if (exec->prior_layer < (*token)->prior)
		manage_parenthesis(exec, token, 0);
	if (exec->prior_layer > (*token)->prior)
		return (1);
	return (0);
}

/*REVIEW - invoke_programs

//	1)	If the executable is not a builtin and is invalid, we stop;
	2)	If it is a builtin, we do it without fork.
		exec->builtins is an array of functions;
	3)	We fork.
	3.1)If pid is invalid, we kill the process;
	3.2)If pid == 0, we are in the child. We launch execve. If fails, we
		clean the memory;
	3.3)Else, we are in main process, and we continue;
	4)	We save the pid in a array of pids;
	5)	If we have printed on a pipe STDOUT, we dup the pipe STDIN.
*/
static int	invoke_programs(t_exec *exec, int i)
{
	pid_t	pid;

	if (!exec->commands[i] || !exec->commands[i][0])
		return (0);
	if (is_a_valid_executable(exec, i) == _NO)
		return (0);
	if (exec->which_cmd[i] != 0)
		return ((exec->builtins[(int)exec->which_cmd[i]]) \
		(exec->commands[i], exec));
	pid = fork();
	if (pid < 0)
		error(E_FORK, exec);
	else if (pid == 0)
	{
		close_all(exec);
		execve(exec->commands[i][0], exec->commands[i], *exec->env);
		bash_message(E_CMD_NOTFOUND, exec->commands[i][0]);
		return (set_exit_code(exec, 127), exit_process(exec), 1);
	}
	exec->pid_list[i] = pid;
	return (0);
}

/*REVIEW - wait_everyone

//	1)	We reset STDIN and STDOUT;
	2)	We set an index to the last command done index;
	3)	We wait all pids until last cmd done;
	4)	If a pid exist and it's the last command, update the exit status;
	5)	We set last_command_done to i.
*/
int	wait_everyone(t_exec *exec)
{
	int		i;
	int		exit_code;

	exit_code = 0;
	dup2(exec->stdin_fd, 0);
	dup2(exec->stdout_fd, 1);
	i = 0;
	while (i != exec->last_cmd)
	{
		if (exec->pid_list[i])
		{
			waitpid(exec->pid_list[i], &exit_code, 0);
			if (i == exec->curr_cmd - 1)
				*exec->exit_code = exit_code / 256;
			exec->pid_list[i] = 0;
		}
		++i;
	}
	return (0);
}
