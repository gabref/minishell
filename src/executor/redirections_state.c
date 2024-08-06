/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:35:46 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 10:35:47 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

void	save_redirection_state(t_minishell *ms)
{
	ms->saved_stdin = dup(STDIN_FILENO);
	ms->saved_stdout = dup(STDOUT_FILENO);
	ms->saved_stderr = dup(STDERR_FILENO);
}

void	restore_redirection_state(t_minishell *ms)
{
	dup2(ms->saved_stdin, STDIN_FILENO);
	dup2(ms->saved_stdout, STDOUT_FILENO);
	dup2(ms->saved_stderr, STDERR_FILENO);
	close(ms->saved_stdin);
	close(ms->saved_stdout);
	close(ms->saved_stderr);
}
