/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:02 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/15 17:32:08 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/minishell.h"
#include "../../inc/utils.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	if (ac != 1 || av[1])
	{
		ft_printf(RED MSG_ERR_ARGS RST);
		exit(EXIT_FAILURE);
	}
	(void)envp;
	init_minishell(&ms, NULL);
	print_welcome();
	print_envs(ms.env);
	ms_set_env(&ms, "PWD", "/home/galves-f");
	ms_set_env(&ms, "USER", "gian piero");
	ms_set_env(&ms, "LOGPOSE", "gian piero");
	ms_set_env(&ms, "LOGPOSE", "gian piero");
	print_envs(ms.env);
	append_history(&ms, "ls -l");
	append_history(&ms, "ls -la");
	append_history(&ms, "pwd");
	append_history(&ms, "ls -la | grep ciao");
	append_history(&ms, "bella > stdout");
	append_history(&ms, "jq {}");
	ft_printf("his[1]: %s\n", get_history_idx(&ms, 1));
	ft_printf("his[2]: %s\n", get_history_idx(&ms, 2));
	ft_printf("his[9]: %s\n", get_history_idx(&ms, 9));
	ft_printf("his[-1]: %s\n", get_history_idx(&ms, -1));
	print_history(&ms);
	destroy_minishell(&ms);
	return (0);
}
