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

char	*get_path_for_executable(t_minishell *ms, char *command, int *exit_code)
{
	char	*path;
	char	*path_env;
	char	*cmd_path;
	char	**path_dirs;
	int		i;
	int		file_permissions;

	if (ft_strchr(command, '/'))
	{
		if (is_directory(command))
		{
			ft_putstr_fd(" Is a directory\n", STDERR_FILENO);
			*exit_code = 126;
			return (NULL);
		}
		file_permissions = check_file_permissions(command, X_OK);
		if (file_permissions == FILE_NOT_FOUND_ERROR)
		{
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
			*exit_code = 127;
			return (NULL);
		}
		else if (file_permissions == PERMISSION_CHECK_ERROR)
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
	path = NULL;
	path_env = ms_get_env(ms, "PATH");
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
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
	free(path_env);
	ft_free_2d_array((void **)path_dirs);
	if (cmd_path == NULL)
	{
		*exit_code = 127;
		ft_putstr_fd(" command not found\n", STDERR_FILENO);
	}
	return (cmd_path);
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

