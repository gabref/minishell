/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 02:05:29 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 02:05:32 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

const t_builtin	*get_builtins(void)
{
	static const t_builtin	builtins[] = {{"echo", builtin_echo}, {"cd",
			builtin_cd}, {"pwd", builtin_pwd}, {"export", builtin_export},
			{"unset", builtin_unset}, {"env", builtin_env}, {"exit",
			builtin_exit}, {"clear", builtin_clear}, {NULL, NULL}};

	return (builtins);
}

bool	is_builtin(char *command)
{
	const t_builtin	*builtins;
	int				i;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(command, builtins[i].name, ft_strlen(command)) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	execute_builtin(t_minishell *ms, t_command *command)
{
	const t_builtin	*builtins;
	int				i;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(command->command, builtins[i].name,
				ft_strlen(command->command)) == 0)
		{
			builtins[i].builtin_func(ms, command->args);
			return ;
		}
		i++;
	}
	ft_putstr_fd("Unknown builtin command\n", STDOUT_FILENO);
}
