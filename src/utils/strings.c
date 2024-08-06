/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:00:50 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:47:45 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	add_string_front(char ***array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (*array)
		while ((*array)[i])
			i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	i = 0;
	new_array[0] = str;
	if (*array)
	{
		while ((*array)[i])
		{
			new_array[i + 1] = (*array)[i];
			i++;
		}
		free(*array);
	}
	new_array[i + 1] = NULL;
	*array = new_array;
}

int	find_string_2d_array(char *str, char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (-1);
	while (arr && arr[i])
	{
		if (ft_strncmp(str, arr[i], ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	substitute_str(char **str, int start, int end, char *sub)
{
	char	*newstr;
	int		sub_len;
	int		i;
	int		newstr_len;
	int		j;

	sub_len = ft_strlen(sub);
	newstr_len = ft_strlen(*str) - (end - start) + sub_len;
	newstr = safe_malloc(sizeof(char) * newstr_len + 1);
	i = -1;
	while (++i < start)
		newstr[i] = (*str)[i];
	j = 0;
	while (i < start + sub_len)
		newstr[i++] = sub[j++];
	while (i < newstr_len)
		newstr[i++] = (*str)[end++];
	newstr[i] = '\0';
	free(*str);
	*str = newstr;
}

void	add_string(char ***array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (*array)
		while ((*array)[i])
			i++;
	new_array = safe_malloc(sizeof(char *) * (i + 2));
	i = 0;
	if (*array)
	{
		while ((*array)[i])
		{
			new_array[i] = (*array)[i];
			i++;
		}
		free(*array);
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	*array = new_array;
}

void	join_string(char **str, char *to_join)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (*(*str + i))
		i++;
	while (to_join[j])
		j++;
	new_str = malloc(sizeof(char) * (i + j + 1));
	i = -1;
	while (*(*str + ++i))
		new_str[i] = *(*str + i);
	free(*str);
	j = 0;
	while (to_join[j])
		new_str[i++] = to_join[j++];
	new_str[i] = '\0';
	*str = new_str;
}
