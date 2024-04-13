/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:40 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/12 18:41:51 by galves-f         ###   ########.fr       */
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

void	destroy_minishell(t_minishell *msh)
{
	(void)msh;
	return ;
}
