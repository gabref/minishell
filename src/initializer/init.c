/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:40 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/01 02:47:14 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/initializers.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include <readline/readline.h>

void	init_minishell(t_minishell *ms, char **env)
{
	ms->ebt = NULL;
	ms->env = get_env_list(env);
	ms->pid = getpid();
	ms->pids = NULL;
	ms->history = (t_history){
		.inputs = NULL,
		.cur_idx = 0,
	};
	ms->last_exit_status = 0;
	ms->saved_stdin = 0;
	ms->saved_stdout = 0;
	ms->saved_stderr = 0;
	ms->exit_ms = -1;
}

void	destroy_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

void	destroy_envs(t_minishell *ms)
{
	t_list	*lst;

	lst = ms->env;
	if (lst != NULL)
		ft_lstclear(&lst, &destroy_env);
	ms->env = NULL;
}

void	destroy_minishell(t_minishell *ms)
{
	if (ms->ebt)
		free_ebt(ms->ebt);
	ms->ebt = NULL;
	destroy_history(ms);
	destroy_envs(ms);
	rl_clear_history();
	return ;
}

void reset_minishell(t_minishell *ms)
{
	if (ms->ebt)
		free_ebt(ms->ebt);
	ms->ebt = NULL;
	return ;
}
