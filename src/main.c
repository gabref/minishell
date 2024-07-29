/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:02 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/29 21:26:31 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/colors.h"
#include "../inc/input.h"
#include "../inc/minishell.h"
#include "../inc/signals.h"
#include "../inc/utils.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;
	char		*line;

	if (ac != 1 || av[1])
	{
		ft_printf(RED MSG_ERR_ARGS RST);
		exit(EXIT_FAILURE);
	}
	config_signals();
	init_minishell(&ms, envp);
	print_welcome();
	while (1)
	{
		reset_minishell(&ms);
		line = get_input(&ms);
		if (!line)
			break ;
		if (!handle_input(&ms, line))
			continue ;
		if (get_global_signal() != 0)
		{
			ms.last_exit_status = get_global_signal() + 128;
			set_global_signal(0);
		}
	}
	destroy_minishell(&ms);
	return (0);
}
