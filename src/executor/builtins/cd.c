/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 02:36:22 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 02:36:23 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"

int	change_directory(t_minishell *ms, char *new_path)
{
	struct stat	path_stat;

	if (stat(new_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode) == 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		ms->last_exit_status = 1;
		return (FAILURE);
	}
	if (chdir(new_path) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		ms->last_exit_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	update_pwd_env(t_minishell *ms)
{
	char	*new_path;
	char	*old_path;

	new_path = getcwd(NULL, PATH_MAX);
	if (new_path == NULL)
	{
		return ;
	}
	old_path = ms_get_env(ms, "PWD");
	ms_set_env(ms, "OLDPWD", old_path);
	ms_set_env(ms, "PWD", new_path);
	free(old_path);
	free(new_path);
}

void	builtin_cd(t_minishell *ms, char **args)
{
	char	*new_path;

	new_path = resolve_new_path(ms, args);
	if (new_path == NULL)
		return ;
	if (change_directory(ms, new_path) == FAILURE)
	{
		free(new_path);
		return ;
	}
	free(new_path);
	update_pwd_env(ms);
}
