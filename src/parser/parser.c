/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:25:57 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 15:02:31 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

t_ebt	*parse_binary_expr(t_minishell *ms, t_list **tokens)
{
	t_ebt	*left;
	t_ebt	*right;
	t_ebt	*ebt;

	left = parse_command(ms, tokens);
	if (left == NULL)
		return (NULL);
	while (is_binary_token(peek(*tokens)))
	{
		t_token *operator= eat(tokens);
		right = parse_command(ms, tokens);
		if (right == NULL)
		{
			free_ebt(left);
			return (NULL);
		}
		ebt = create_ebt();
		ebt->type = convert_type_to_ebt_op(operator->type);
		ebt->left = left;
		ebt->right = right;
		left = ebt;
	}
	return (left);
}

t_ebt	*parse_binary_expr_semicolon(t_minishell *ms, t_list **tokens)
{
	t_ebt	*left;
	t_ebt	*right;
	t_ebt	*ebt;

	left = parse_binary_expr(ms, tokens);
	if (left == NULL)
		return (NULL);
	while (is_binary_token_semicolon(peek(*tokens)))
	{
		t_token *operator= eat(tokens);
		right = parse_binary_expr(ms, tokens);
		if (right == NULL)
		{
			if (ms->last_exit_status != 0)
				return (NULL);
			return (left);
		}
		ebt = create_ebt();
		ebt->type = convert_type_to_ebt_op(operator->type);
		ebt->left = left;
		ebt->right = right;
		left = ebt;
	}
	return (left);
}

t_ebt	*parse_expr(t_minishell *ms, t_list **tokens)
{
	return (parse_binary_expr_semicolon(ms, tokens));
}

t_ebt	*parse(t_minishell *ms, t_lexer *lexer)
{
	t_list	*tokens;
	t_ebt	*ebt;

	tokens = lexer->tokens;
	ebt = NULL;
	while (not_eof(peek(tokens)))
	{
		ebt = parse_expr(ms, &tokens);
		if (ebt == NULL)
			return (NULL);
	}
	return (ebt);
}
