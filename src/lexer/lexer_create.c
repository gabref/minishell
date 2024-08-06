/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:30:55 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:31:42 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	lexer_create_word(t_lexer *lex, char *input)
{
	int				len;
	int				start;
	t_token_type	type;
	char			*value;
	t_token			*token;

	len = 1;
	start = lex->size;
	while (input[start + len] && ft_isprint(input[start + len])
		&& !is_operator(input[start + len])
		&& !is_single_alone_operator(input[start + len])
		&& !is_parenthesis(input[start + len]) && !ft_isspace(input[start
				+ len]))
		len++;
	type = WORD;
	value = ft_substr(input, start, len);
	token = create_token(value, type, lex->size, lex->size + len);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_dollar(t_lexer *lex, char *input)
{
	t_token_type	type;
	char			*value;
	t_token			*token;

	if (ft_strncmp(&input[lex->size], "$?", 2) == 0
		&& ft_isspace(input[lex->size + 2]))
	{
		type = EXIT_STATUS;
		value = ft_substr(input, lex->size, 2);
		token = create_token(value, type, lex->size, lex->size + 2);
		lexer_push_advance(lex, token, input);
		return (true);
	}
	else if (ft_strncmp(&input[lex->size], "$(", 2) == 0)
	{
		type = CMD_SUB;
		value = ft_substr(input, lex->size, 2);
		token = create_token(value, type, lex->size, lex->size + 2);
		lexer_push_advance(lex, token, input);
		return (true);
	}
	return (lexer_create_word(lex, input));
}

static int	handle_single_quotes(const char *input, int start)
{
	int	i;

	i = 1;
	while (input[start + i] && input[start + i] != '\'')
		i++;
	return (i);
}

static int	handle_double_quotes(const char *input, int start)
{
	int	i;

	i = 1;
	while (1)
	{
		while (input[start + i] && input[start + i] != '"' && input[start + i
				- 1] != '\\')
			i++;
		if (input[start + i + 1] == '"')
		{
			i += 2;
			continue ;
		}
		break ;
	}
	return (i);
}

bool	lexer_create_between_quotes(t_lexer *lex, char *input)
{
	t_token_type	type;
	char			*value;
	t_token			*token;
	int				i;
	int				start;

	i = 0;
	start = lex->size;
	if (input[start + i] == '\'')
		i = handle_single_quotes(input, start);
	else if (input[start + i] == '"')
		i = handle_double_quotes(input, start);
	type = WORD;
	value = ft_substr(input, start, i + 1);
	token = create_token(value, type, start, start + i + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}
