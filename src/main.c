/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:02 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/13 00:09:57 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/colors.h"
#include "../inc/minishell.h"
#include "../inc/utils.h"

void print_envs(t_list *env)
{
	t_env	*env_s;

	while (env)
	{
		env_s = (t_env *)env->content;
		ft_printf("%s=%s\n", env_s->key, env_s->value);
		env = env->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	if (ac != 1 || av[1])
	{
		ft_printf(RED MSG_ERR_ARGS RST);
		exit(EXIT_FAILURE);
	}
	init_minishell(&ms, envp);
	print_welcome();
	print_envs(ms.env);
	ms_update_env(&ms, "PWD", "gian piero");
	ms_update_env(&ms, "LOGPOSE", "gian piero");
	print_envs(ms.env);
	destroy_minishell(&ms);
	return (0);
}
