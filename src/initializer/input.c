/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:04:19 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/11 17:10:12 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/initializers.h"

// funzione per pulire lo schermo se l'utente scrive "clear"
void	clean_screen(void)
{
	write(STDOUT_FILENO, "\033[H\033[J", 6);
}

/*	funzione per gestire l'input dell'utente
 */
void	get_input(t_minishell *ms, t_lexer *lex)
{
	char	*input;

	while (1)
	{
		ms->ebt = NULL;
		input = readline("$ ");
		if (input)
		{
			if (ft_strncmp(input, "clear", 5) == 0)
				clean_screen();
			ms_append_history(ms, input);
			lex = lexer(input);
			if (!lex)
			{
				ft_printf("lexer error\n");
				free(input);
			}
			free(input);
		}
	}
}
