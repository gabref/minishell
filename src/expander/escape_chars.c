/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:59:04 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 13:04:43 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/utils.h"

const char	*get_escape_chars(void)
{
	static const char	escape_chars[] = {'\\', '\?', '\a', '\b', '\f', '\n',
		'\r', '\t', '\v'};

	return (escape_chars);
}

const char	**get_escape_strings(void)
{
	static const char	*escape_chars[] = {"\\", "?", "a", "b", "f", "n", "r",
		"t", "v"};

	return (escape_chars);
}

void	substitute_escape_chars(char **str)
{
	int		i;
	int		idx;
	char	*sub;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
		{
			idx = find_string_2d_array((*str + i + 1),
					(char **)get_escape_strings());
			if (idx != -1)
			{
				sub = ft_char_to_string(get_escape_chars()[idx]);
				substitute_str(str, i, i + 2, sub);
				free(sub);
			}
		}
		i++;
	}
}

static int	calculate_new_length(const char *str, const char *escape_chars)
{
	int	i;
	int	newstr_len;

	i = 0;
	newstr_len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (ft_strchr(escape_chars, str[i + 1]))
			{
				newstr_len--;
				i++;
			}
		}
		i++;
	}
	return (newstr_len);
}

void	handle_escape_chars(char **str)
{
	const char	*escape_chars = get_escape_chars();
	int			i;
	int			j;
	char		*newstr;
	int			newstr_len;

	newstr_len = calculate_new_length(*str, escape_chars);
	newstr = safe_malloc(sizeof(char) * newstr_len + 1);
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
			if (ft_strchr(escape_chars, (*str)[i + 1]))
				i++;
		newstr[j++] = (*str)[i++];
	}
	newstr[j] = '\0';
	free(*str);
	*str = newstr;
}
