/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:31:27 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:14 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"

t_ebt	*handle_error(t_minishell *ms, const char *message)
{
	if (ms->last_exit_status == 0)
		ft_printf(RED "%s\n" RST, message);
	ms->last_exit_status = 1;
	return (NULL);
}

bool	handle_error_command(t_minishell *ms, t_command *command,
		const char *message, const char *c)
{
	if (ms->last_exit_status == 0)
		ft_printf(RED "%s %s\n" RST, message, c);
	ms->last_exit_status = 1;
	free_command(command);
	return (false);
}

bool	handle_error_redir(t_minishell *ms, t_command *command, t_redir *redir,
		const char *c)
{
	if (ms->last_exit_status == 0)
		ft_printf(RED "Error: expected filename after '%s'\n" RST, c);
	ms->last_exit_status = 1;
	free_command(command);
	free(redir->filename);
	free(redir);
	return (false);
}
