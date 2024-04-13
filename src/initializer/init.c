/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:40 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/13 16:13:17 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/initializers.h"
#include "../../inc/minishell.h"

void	init_minishell(t_minishell *msh, char **env)
{
	msh->ebt = NULL;
	msh->env = get_env_list(env);
	msh->pid = getpid();
	msh->pids = NULL;
	msh->history = (t_history){
		.inputs = NULL,
		.cur_idx = 0,
	};
	msh->last_exit_status = 0;
}

static void	destroy_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

static void	destroy_envs(t_minishell *ms)
{
	t_list	*lst;

	lst = ms->env;
	ft_lstclear(&lst, &destroy_env);
}

void	destroy_minishell(t_minishell *msh)
{
	destroy_envs(msh);
	return ;
}
