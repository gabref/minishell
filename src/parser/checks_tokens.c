/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:54:23 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:54:24 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	is_primary_token(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == WORD || token->type == INSTRUCTION
		|| token->type == DOLLAR || token->type == EXIT_STATUS
		|| token->type == CMD_SUB || token->type == SINGLE_Q
		|| token->type == DOUBLE_Q || token->type == BSLASH
		|| token->type == O_ANGLE_BRACKET || token->type == C_ANGLE_BRACKET
		|| token->type == O_DANGLE_BRACKET || token->type == C_DANGLE_BRACKET);
}

int	is_binary_token_semicolon(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == SEMICOLON);
}

int	is_binary_token(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == DAND || token->type == OR || token->type == PIPE);
}
