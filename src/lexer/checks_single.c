/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:30:38 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:30:39 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

bool	is_parenthesis(char c)
{
	return (c == '(' || c == ')' || c == '{' || c == '}' || c == '['
		|| c == ']');
}

bool	is_dollar(char c)
{
	return (c == '$');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_operator(char c)
{
	return (c == '<' || c == '|' || c == '>');
}
