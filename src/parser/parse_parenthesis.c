/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:58:15 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 20:58:15 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

t_ebt	*parse_bracket_parenthesis(t_minishell *ms, t_list **tokens,
		t_token *token)
{
	t_ebt	*ebt;

	ebt = create_ebt();
	ebt->type = EBT_OP_SUBSHELL;
	ebt->left = parse_expr(ms, tokens);
	if (ebt->left == NULL || !tokens || !*tokens || !peek(*tokens)->value)
		if (expect(ms, tokens, token->type + 1,
				"syntax error near unexpected ')'\n") == NULL)
		{
			free_ebt(ebt);
			return (NULL);
		}
	if (expect(ms, tokens, token->type + 1,
			"expected closing bracket\n") == NULL)
	{
		free_ebt(ebt);
		return (NULL);
	}
	return (ebt);
}

t_ebt	*parse_curly_parenthesis(t_minishell *ms, t_list **tokens,
		t_token *token)
{
	t_ebt	*ebt;

	ebt = create_ebt();
	ebt->type = EBT_OP_SUBSHELL;
	ebt->left = parse_expr(ms, tokens);
	if (ebt->left == NULL || !tokens || !*tokens || !peek(*tokens)->value)
		if (expect(ms, tokens, token->type + 1,
				"syntax error near unexpected '}'\n") == NULL)
		{
			free_ebt(ebt);
			return (NULL);
		}
	if (expect(ms, tokens, token->type + 1,
			"expected closing curly bracket\n") == NULL)
	{
		free_ebt(ebt);
		return (NULL);
	}
	return (ebt);
}

t_ebt	*parse_square_parenthesis(t_minishell *ms, t_list **tokens,
		t_token *token)
{
	t_ebt	*ebt;

	ebt = create_ebt();
	ebt->type = EBT_OP_SUBSHELL;
	ebt->left = parse_expr(ms, tokens);
	if (ebt->left == NULL || !tokens || !*tokens || !peek(*tokens)->value)
		if (expect(ms, tokens, token->type + 1,
				"syntax error near unexpected ']'\n") == NULL)
		{
			free_ebt(ebt);
			return (NULL);
		}
	if (expect(ms, tokens, token->type + 1,
			"expected closing square bracket\n") == NULL)
	{
		free_ebt(ebt);
		return (NULL);
	}
	return (ebt);
}

t_ebt	*parse_parenthesis(t_minishell *ms, t_list **tokens, t_token *token)
{
	t_ebt	*ebt;

	eat(tokens);
	if (token->type == O_BRACKETS)
		ebt = parse_bracket_parenthesis(ms, tokens, token);
	else if (token->type == O_CURLY)
		ebt = parse_curly_parenthesis(ms, tokens, token);
	else if (token->type == O_SQUARE)
		ebt = parse_square_parenthesis(ms, tokens, token);
	else
	{
		ebt = parse_expr(ms, tokens);
		if (expect(ms, tokens, C_PARENTHESES, "expected ')'\n") == NULL)
		{
			free_ebt(ebt);
			return (NULL);
		}
	}
	return (ebt);
}
