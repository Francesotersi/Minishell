/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:15:38 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/27 16:05:56 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

//ANCHOR - Enums

/*REVIEW - token types 

	Token are organized by 12 types.
	Here's the explanation for all of those:
	
	0)	COMMAND:		grep, ls...
	1)	ARGUMENT:		-n, filename, ../ ...
	2)	FILES:			filename, EOF...
	3)	RED_OUT:		>
	4)	RED_IN:			<
	5)	RED_O_APPEND:	>>
	6)	HERE_DOC:		<<
	7)	PIPE:			|
	8)	AND:			&&
	9)	OR:				||
	10)	PARENTHESIS:	(, )
	11)	RED_SUBSHELL:	redirect subshell: cat <(ls)
*/
enum e_types
{
	COMMAND,
	ARGUMENT,
	FILES,
	RED_OUT,
	RED_IN,
	RED_O_APPEND,
	HERE_DOC,
	PIPE,
	AND,
	OR,
	PARENTHESIS,
	RED_SUBSHELL,
	NONE,
};

/*REVIEW - builtins enum

	Builtins enum. BUILT_N is used to allocate
	t_builtin *builtins
*/
enum e_builtin
{
	B_ECHO = 1,
	B_CD = 2,
	B_PWD = 3,
	B_EXPORT = 4,
	B_UNSET = 5,
	B_ENV = 6,
	B_EXIT = 7,
	BUILT_N = 8,
};

/*REVIEW - permissions enum

	Every file opened with open in the program has a
	set of permissions allowed, using bitwise
	operations.
*/
enum e_permissions
{
	INFILE = O_RDONLY,
	INFILE_DOC = O_RDWR | O_CREAT,
	OUTFILE_TRUNC = O_RDWR | O_CREAT | O_TRUNC,
	OUTFILE_APPEND = O_RDWR | O_CREAT | O_APPEND,
};

/*REVIEW - error enum 

	Error enum, used to print different error messages 
	in the function bash_message() and error()
*/
enum e_exec_errors
{
	NO_ERR,
	E_ARGS,
	E_MALLOC,
	E_OPEN,
	E_FORK,
	E_HEREDOC_CTRL_D,
	E_NOENV,
	E_EXPORT_PARSING,
	E_UNSET_PARSING,
	E_ENV_PARSING,
	E_ENV_DIRECTORY,
	E_ENV_NOTFOUND,
	E_ENV_EXE,
	E_ENV_PERMISSION,
	E_CD,
	E_CD_ARGS,
	E_CD_PATH,
	E_CD_ENV,
	E_EXIT_NUMERIC,
	E_EXIT_ARGS,
	E_NOFILE,
	E_CMD_NOTFOUND,
	E_IS_DIRECTORY,
	E_PERMISSION_DENIED,
	E_PROC_SUB,
};

/*REVIEW - sub_strlen enum 

	sub_strlen and sub_strcpy are utilities functions,
	that counts/copy strings until a set of characters
	is INCLUDED/EXCLUDED.

	string = ffffile.txt
	_sub_strlen(string, ".", INCL) = 4
	_sub_strlen(string, ".", EXCL) = 7
*/
enum e_sub_strlen
{
	INCL,
	EXCL,
};

/*REVIEW - environment enum

	//TODO - 
*/
enum e_environment
{
	ENV_NO_EQ_PLUS = 0,
	ENV_NAME_SIZE = 1,
	ENV_CONT_SIZE = 2,
	ENV_WHICH_VAL = 3,
};

/*REVIEW - sub_strlen enum

	boolean yes/no. Stop is set here to avoid creating
	a new enum
*/
enum e_bools
{
	_NO = 0,
	_YES = 1,
	_STOP = 2,
};

enum e_signal
{
	CTRL_C = 10,
	CTRL_D = 20,
	CTRL_BACK = 30,
};

#endif