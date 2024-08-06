/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_small.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:30:59 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:31:00 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	lexer_create_parenthesis(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (input[lex->size] == '(')
		type = O_BRACKETS;
	else if (input[lex->size] == ')')
		type = C_BRACKETS;
	else if (input[lex->size] == '{')
		type = O_CURLY;
	else if (input[lex->size] == '}')
		type = C_CURLY;
	else if (input[lex->size] == '[')
		type = O_BRACKETS;
	else if (input[lex->size] == ']')
		type = C_BRACKETS;
	value = ft_char_to_string(input[lex->size]);
	token = create_token(value, type, lex->size, lex->size + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_operator(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (input[lex->size] == '&')
		type = AND;
	if (input[lex->size] == '|')
		type = PIPE;
	else if (input[lex->size] == '<')
		type = O_ANGLE_BRACKET;
	else if (input[lex->size] == '>')
		type = C_ANGLE_BRACKET;
	else if (input[lex->size] == '!')
		type = MARK;
	else if (input[lex->size] == '+')
		type = OPERATORS;
	else if (input[lex->size] == '-')
		type = OPERATORS;
	value = ft_char_to_string(input[lex->size]);
	token = create_token(value, type, lex->size, lex->size + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_single_alone_operator(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (input[lex->size] == ';')
		type = SEMICOLON;
	else if (input[lex->size] == '\n')
		type = N_LINE;
	else if (input[lex->size] == '\\')
		type = BSLASH;
	value = ft_char_to_string(input[lex->size]);
	token = create_token(value, type, lex->size, lex->size + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_double_operator(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (ft_strncmp(&input[lex->size], "&&", 2) == 0)
		type = DAND;
	if (ft_strncmp(&input[lex->size], "||", 2) == 0)
		type = OR;
	if (ft_strncmp(&input[lex->size], "<<", 2) == 0)
		type = O_DANGLE_BRACKET;
	if (ft_strncmp(&input[lex->size], ">>", 2) == 0)
		type = C_DANGLE_BRACKET;
	value = ft_substr(input, lex->size, 2);
	token = create_token(value, type, lex->size, lex->size + 2);
	lexer_push_advance(lex, token, input);
	return (true);
}
