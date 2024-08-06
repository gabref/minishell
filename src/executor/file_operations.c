/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:52:15 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 11:58:40 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/utils.h"

int	check_file_permissions(const char *filepath, int flags)
{
	struct stat	file_stat;

	if (access(filepath, F_OK) != 0)
		return (FILE_NOT_FOUND_ERROR);
	if (stat(filepath, &file_stat) != 0)
		return (PERMISSION_CHECK_ERROR);
	if (!S_ISREG(file_stat.st_mode))
		return (FILE_NOT_FOUND_ERROR);
	if (access(filepath, flags) != 0)
		return (PERMISSION_CHECK_ERROR);
	return (PERMISSIONS_OK);
}

char	*read_file_to_string(int fd)
{
	char	*file_as_string;
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	file_as_string = ft_strdup("");
	while (line != NULL)
	{
		tmp = file_as_string;
		file_as_string = ft_strjoin(tmp, line);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	return (file_as_string);
}

int	is_directory(char *command)
{
	struct stat	path_stat;

	if (stat(command, &path_stat) == 0 && S_ISDIR(path_stat.st_mode) == 1)
		return (1);
	return (0);
}

char	**get_envs(t_list *envs)
{
	char	**env;
	t_list	*node;
	t_env	*env_node;
	int		i;

	i = 0;
	node = envs;
	while (node)
	{
		i++;
		node = node->next;
	}
	env = safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	node = envs;
	while (node)
	{
		env_node = (t_env *)node->content;
		env[i] = ft_strjoin(env_node->key, "=");
		env[i] = ft_strjoin(env[i], env_node->value);
		node = node->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
