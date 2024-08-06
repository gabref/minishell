/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:55:10 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 12:55:40 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/utils.h"

void	handle_around_single_quotes(char **str)
{
	if ((*str)[0] == '\'')
		substitute_str(str, 0, 1, "");
	if ((*str)[ft_strlen(*str) - 1] == '\'')
		substitute_str(str, ft_strlen(*str) - 1, ft_strlen(*str), "");
}

void	handle_around_double_quotes(char **str)
{
	if ((*str)[0] == '\"')
		substitute_str(str, 0, 1, "");
	if (ft_strlen(*str) > 2 && (*str)[ft_strlen(*str) - 1] == '\"'
		&& (*str)[ft_strlen(*str) - 2] != '\\')
		substitute_str(str, ft_strlen(*str) - 1, ft_strlen(*str), "");
}

void	handle_quotes(char **str)
{
	int	i;
	int	start;

	start = 0;
	if ((*str)[0] == '"')
		start = 1;
	i = start;
	while ((*str)[i])
	{
		if ((!start && (*str)[i] == '\'') || (*str)[i] == '\"')
		{
			substitute_str(str, i, i + 1, "");
			i = start;
			continue ;
		}
		else if ((*str)[i] == '\\' && ((*str)[i + 1] == '\'' || (*str)[i
				+ 1] == '"'))
		{
			substitute_str(str, i, i + 2, "");
			i = start;
			continue ;
		}
		i++;
	}
}
