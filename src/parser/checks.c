/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:54:30 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:54:31 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	is_open_parenthesis(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == O_SQUARE || token->type == O_CURLY
		|| token->type == O_BRACKETS);
}

int	is_close_parenthesis(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == C_SQUARE || token->type == C_CURLY
		|| token->type == C_BRACKETS);
}

int	is_angle_bracket(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == O_ANGLE_BRACKET || token->type == C_ANGLE_BRACKET
		|| token->type == O_DANGLE_BRACKET || token->type == C_DANGLE_BRACKET);
}
