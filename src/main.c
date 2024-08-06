/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:02 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 20:57:48 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/colors.h"
#include "../inc/executor.h"
#include "../inc/input.h"
#include "../inc/minishell.h"
#include "../inc/signals.h"
#include "../inc/utils.h"

static void	check_arguments(int ac, char **av)
{
	if (ac != 1 || av[1])
	{
		ft_printf(RED MSG_ERR_ARGS RST);
		exit(EXIT_FAILURE);
	}
}

static void	initialize_minishell(t_minishell *ms, char **envp)
{
	config_signals();
	init_minishell(ms, envp);
	print_welcome();
}

static int	main_loop(t_minishell *ms)
{
	char	*line;
	int		ret;

	ret = 0;
	while (1)
	{
		reset_minishell(ms);
		line = get_input(ms);
		if (!line)
			break ;
		if (!handle_input(ms, line))
			continue ;
		executor(ms);
		if (get_global_signal() != 0)
		{
			ms->last_exit_status = get_global_signal() + 128;
			set_global_signal(0);
		}
		if (ms->exit_ms != -1)
		{
			ret = ms->exit_ms;
			break ;
		}
	}
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;
	int			ret;

	ret = 0;
	check_arguments(ac, av);
	initialize_minishell(&ms, envp);
	ret = main_loop(&ms);
	destroy_minishell(&ms);
	return (ret);
}
