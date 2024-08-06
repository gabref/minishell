/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:40:12 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 09:40:12 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"
#include "../../../inc/utils.h"

void	builtin_echo(t_minishell *ms, char **args)
{
	bool	newline;
	int		i;

	(void)ms;
	newline = true;
	i = 0;
	if (find_string_2d_array("-n", args) == 0)
		newline = false;
	while (args && args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
