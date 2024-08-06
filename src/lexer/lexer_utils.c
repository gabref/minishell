/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:31:04 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:31:04 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	lexer_advance(t_lexer *lexer, char *input)
{
	if (input[lexer->size] != '\0' && lexer->size <= (int)ft_strlen(input))
		lexer->size++;
}

void	lexer_skip_whitespace(t_lexer *lexer, char *input)
{
	while (input[lexer->size] && ft_isspace(input[lexer->size]))
		lexer_advance(lexer, input);
}

void	lexer_push_token(t_lexer *lex, t_token *token)
{
	if (!lex->tokens)
		lex->tokens = ft_lstnew(token);
	else
		ft_lstadd_back(&lex->tokens, ft_lstnew(token));
}

void	lexer_push_advance(t_lexer *lex, t_token *token, char *input)
{
	int	i;

	lexer_push_token(lex, token);
	i = -1;
	while (++i < token->current_idx - token->input_start_idx)
		lexer_advance(lex, input);
}
