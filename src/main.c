/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:02 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/11 17:11:21 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/colors.h"
#include "../inc/minishell.h"
#include "../inc/lexer.h"
#include "../inc/initializers.h"
#include "../inc/utils.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;
	t_lexer		lex;

	if (ac != 1 || av[1])
	{
		ft_printf(RED MSG_ERR_ARGS RST);
		exit(EXIT_FAILURE);
	}
	init_minishell(&ms, envp);
	print_welcome();
	get_input(&ms, &lex);
	// expander(&ms);
	destroy_minishell(&ms);
	return (0);
}
