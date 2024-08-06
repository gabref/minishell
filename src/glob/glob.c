/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:50:17 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 13:50:21 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/glob.h"

bool	match_pattern(const char *pattern, const char *filename)
{
	if (*pattern == '\0')
		return (*filename == '\0');
	if (*pattern == '*')
		return (match_pattern(pattern + 1, filename) || (*filename
				&& match_pattern(pattern, filename + 1)));
	if (*pattern == *filename)
		return (match_pattern(pattern + 1, filename + 1));
	return (false);
}

static void	add_to_expanded_args(char *entry_name, char ***expanded_args,
		int *expanded_count)
{
	char	**new_expanded_args;

	new_expanded_args = safe_malloc(sizeof(char *) * (*expanded_count + 1));
	if (*expanded_args)
	{
		memcpy(new_expanded_args, *expanded_args, sizeof(char *)
			* (*expanded_count));
		free(*expanded_args);
	}
	new_expanded_args[*expanded_count] = ft_strdup(entry_name);
	*expanded_args = new_expanded_args;
	(*expanded_count)++;
}

static char	**copy_and_free_args(char **args, char **expanded_args,
		int expanded_count)
{
	char	**final_expanded_args;

	final_expanded_args = safe_malloc(sizeof(char *) * (expanded_count + 1));
	memcpy(final_expanded_args, expanded_args, sizeof(char *) * expanded_count);
	final_expanded_args[expanded_count] = NULL;
	free(expanded_args);
	ft_free_2d_array((void **)args);
	return (final_expanded_args);
}

static void	expand_single_argument(char *arg, char ***expanded_args,
		int *expanded_count)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		ft_putstr_fd("Error: opendir failed\n", STDERR_FILENO);
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(arg, entry->d_name))
			add_to_expanded_args(entry->d_name, expanded_args, expanded_count);
		entry = readdir(dir);
	}
	closedir(dir);
}

char	**expand_wildcard(char **args)
{
	char	**expanded_args;
	int		expanded_count;
	int		i;

	expanded_args = NULL;
	expanded_count = 0;
	i = 0;
	while (args && args[i])
	{
		if (ft_strchr(args[i], '*') != NULL)
			expand_single_argument(args[i], &expanded_args, &expanded_count);
		else
			add_to_expanded_args(args[i], &expanded_args, &expanded_count);
		i++;
	}
	expanded_args = copy_and_free_args(args, expanded_args, expanded_count);
	return (expanded_args);
}
