/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:04:19 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/30 14:05:11 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/expander.h"
#include "../../inc/input.h"
#include "../../inc/parser.h"
#include <unistd.h>

// funzione per pulire lo schermo se l'utente scrive "clear"
void	clean_screen(void)
{
	write(STDOUT_FILENO, "\033[H\033[J", 6);
}

char	*get_input(t_minishell *ms)
{
	char	*input;

	if (ms->ebt)
		free_ebt(ms->ebt);
	ms->ebt = NULL;
	input = readline("$> ");
	if (!input)
	{
		ft_printf(RED "exit\n" RST);
		return (NULL);
	}
	if (input[0] != '\0')
		ms_append_history(ms, input);
	return (input);
}

bool	handle_input(t_minishell *ms, char *input)
{
	t_lexer	*lex;
	t_ebt	*parser;

	lex = lexer(input);
	if (!lex)
	{
		ft_printf(RED "lexer error\n" RST);
		free(input);
		return (false);
	}
	free(input);
	expander(ms, lex);
	parser = parse(ms, lex);
	free_lexer(lex);
	if (!parser)
	{
		ft_printf(RED "parser error\n" RST);
		return (1);
	}
	ms->ebt = parser;
	return (true);
}
