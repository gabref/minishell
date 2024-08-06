/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:30:35 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:31:24 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	is_single_alone_operator(char c)
{
	return (c == ';' || c == '\n' || c == '\\');
}

bool	is_single_operator(char *input, int idx)
{
	if (!input)
		return (false);
	return (is_operator(input[idx]) && !is_operator(input[idx + 1]));
}

bool	is_double_operator(char *input, int idx)
{
	char	c;

	if (!input)
		return (false);
	c = input[idx];
	return ((c == '|' || c == '&' || c == '<' || c == '>') && c == input[idx
			+ 1]);
}
