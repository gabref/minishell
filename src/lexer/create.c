/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:30:42 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:30:44 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include "../../inc/utils.h"

t_token	*create_empty_token(void)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	token->input_start_idx = 0;
	token->current_idx = 0;
	token->value = NULL;
	token->type = 0;
	return (token);
}

t_token	*create_token(char *value, t_token_type type, int input_start_idx,
		int current_idx)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	token->input_start_idx = input_start_idx;
	token->current_idx = current_idx;
	token->value = value;
	token->type = type;
	return (token);
}

t_lexer	*create_lexer(void)
{
	t_lexer	*lexer;

	lexer = safe_malloc(sizeof(t_lexer));
	lexer->size = 0;
	lexer->tokens = NULL;
	return (lexer);
}
