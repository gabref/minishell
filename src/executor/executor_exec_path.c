/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exec_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:08:30 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 12:13:47 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

static char	*check_local_executable(char *command, int *exit_code)
{
	if (is_directory(command))
	{
		ft_putstr_fd(" Is a directory\n", STDERR_FILENO);
		*exit_code = 126;
		return (NULL);
	}
	if (check_file_permissions(command, X_OK) == FILE_NOT_FOUND_ERROR)
	{
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		*exit_code = 127;
		return (NULL);
	}
	else if (check_file_permissions(command, X_OK) == PERMISSION_CHECK_ERROR)
	{
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		*exit_code = 126;
		return (NULL);
	}
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	*exit_code = 127;
	ft_printf("command not found: %s\n", command);
	return (NULL);
}

void	handle_command_not_found_cleanup(char *cmd_path, int *exit_code,
		char *path_env, char **path_dirs)
{
	free(path_env);
	ft_free_2d_array((void **)path_dirs);
	if (cmd_path != NULL)
		return ;
	*exit_code = 127;
	ft_putstr_fd(" command not found\n", STDERR_FILENO);
}

char	*get_command_path_from_env(t_minishell *ms, char *command,
		int *exit_code)
{
	char	*path;
	char	*path_env;
	char	*cmd_path;
	char	**path_dirs;
	int		i;

	path_env = ms_get_env(ms, "PATH");
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	cmd_path = NULL;
	while (path_dirs[i])
	{
		path = ft_strjoin(path_dirs[i++], "/");
		cmd_path = ft_strjoin(path, command);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		free(path);
		free(cmd_path);
		cmd_path = NULL;
	}
	handle_command_not_found_cleanup(cmd_path, exit_code, path_env, path_dirs);
	return (cmd_path);
}

char	*get_path_for_executable(t_minishell *ms, char *command, int *exit_code)
{
	char	*cmd_path;

	if (ft_strchr(command, '/'))
		return (check_local_executable(command, exit_code));
	cmd_path = get_command_path_from_env(ms, command, exit_code);
	return (cmd_path);
}
