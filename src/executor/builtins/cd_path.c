/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 02:36:27 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 02:36:27 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"

char	*resolve_home(t_minishell *ms)
{
	char	*home;

	home = ms_get_env(ms, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("no HOME env variable set\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return (NULL);
	}
	return (home);
}

char	*resolve_oldpwd(t_minishell *ms)
{
	char	*old_pwd;

	old_pwd = ms_get_env(ms, "OLDPWD");
	if (old_pwd == NULL)
	{
		ft_putstr_fd("no OLDPWD env variable set\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return (NULL);
	}
	return (old_pwd);
}

char	*resolve_new_path(t_minishell *ms, char **args)
{
	char	*new_path;

	new_path = NULL;
	if (args && args[0] && args[1])
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return (NULL);
	}
	if (args != NULL && args[0] != NULL)
		new_path = args[0];
	if (new_path == NULL)
		new_path = resolve_home(ms);
	else if (ft_strncmp(new_path, "~", 1) == 0)
		new_path = resolve_home(ms);
	else if (ft_strncmp(new_path, "-", 1) == 0)
		new_path = resolve_oldpwd(ms);
	else
		new_path = ft_strdup(new_path);
	return (new_path);
}
