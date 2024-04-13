/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:55:48 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/13 09:42:02 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/ft_printf/inc/ft_printf.h"
# include "../libs/libft/inc/libft.h"
# include <stdio.h>

/*
 *	t_history
 *		- inputs: list of strings
 *		- cur_idx: index of the current input
 */
typedef struct s_history
{
	t_list			*inputs;
	int				cur_idx;
}					t_history;

/*
 *	t_env
 *		- key: environment variable name
 *		- value: environment variable value
 */
typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef enum e_ebt_op
{
	EBT_OP_OR,
	EBT_OP_AND,
	EBT_OP_PIPE,
	EBT_OP_COMMAND,
	EBT_OP_SUBSHELL,
	EBT_OP_SEMICOLON,
	EBT_OP_COMMAND_SUBS,
}					t_ebt_op;

typedef struct s_command
{
	char			*command;
	char			**args;
	char			*heredoc_file_name;
}					t_command;

/*
 * Binary Executor Tree
 *		- command: command to be executed (if type is EBT_OP_COMMAND, else NULL)
 *		- type: type of operation
 *		- left: left node
 *		- right: right node
 */
typedef struct s_ebt
{
	t_command		*command;
	t_ebt_op		type;
	struct s_ebt	*left;
	struct s_ebt	*right;
}					t_ebt;

/*
 *	t_minishell
 *		- last_exit_status: last exit status of a command
 *		- pid: process id of the current process
 *		- pids: process ids of the child processes
 *		- ebt: binary executor tree
 *		- env: list of environment variables
 *		- history: history of inputs
 */
typedef struct s_minishell
{
	int				last_exit_status;
	pid_t			pid;
	pid_t			*pids;
	t_ebt			*ebt;
	t_list			*env;
	t_history		history;
}					t_minishell;

/* initializes the minishell struct */
void				init_minishell(t_minishell *msh, char **env);
/* frees all the memory allocated for the minishell */
void				destroy_minishell(t_minishell *msh);

/* UTILS */

/* gets the value of a env variable with name key */
char				*ms_get_env(t_minishell *ms, char *key);
/* 
   sets the value of a env variable with name key 
   if the variable does not exist, it is created
   else its value is updated
*/
int	ms_set_env(t_minishell *ms, char *key, char *value);

#endif
