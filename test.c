# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_data
{
	char	*input;
	int		exit_code;
	char	**env;
	
} t_data;

int	start(t_data *gen)
{
	while (1)
	{
		gen->input = readline("minishell$> ");
		if (!gen->input)
			return(write(1, "exit\n", 5), 0);
		if (gen->input[0] != '\0')
			add_history(gen->input);
		free(gen->input);
	}
	return (0);
}

int	main()
{
	t_data data = (t_data){0};
	start(&data);
}