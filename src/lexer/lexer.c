/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:30:48 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:30:51 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include "../../inc/colors.h"

bool	lexer_get_tokens(t_lexer *lex, char *input)
{
	bool	success;

	success = true;
	while (input[lex->size] && success)
	{
		lexer_skip_whitespace(lex, input);
		if (input[lex->size] == '\0')
			break ;
		if (is_parenthesis(input[lex->size]))
			success = lexer_create_parenthesis(lex, input);
		else if (is_single_alone_operator(input[lex->size]))
			success = lexer_create_single_alone_operator(lex, input);
		else if (is_single_operator(input, lex->size))
			success = lexer_create_operator(lex, input);
		else if (is_double_operator(input, lex->size))
			success = lexer_create_double_operator(lex, input);
		else if (is_dollar(input[lex->size]))
			success = lexer_create_dollar(lex, input);
		else if (is_quote(input[lex->size]))
			success = lexer_create_between_quotes(lex, input);
		else
			success = lexer_create_word(lex, input);
	}
	return (success);
}

void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free(token->value);
	free(token);
}

void	free_lexer(t_lexer *lex)
{
	ft_lstclear(&lex->tokens, free_token);
	free(lex);
}

t_lexer	*lexer(char *input)
{
	t_lexer	*lex;

	lex = create_lexer();
	if (lexer_get_tokens(lex, input))
		return (lex);
	ft_printf(RED "Lexer error\n" RST);
	return (NULL);
}
