/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:40:14 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 11:48:33 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/minishell.h"

int	handle_and(t_minishell *ms, t_ebt *ebt)
{
	int	l_status;
	int	r_status;

	l_status = SUCCESS;
	r_status = SUCCESS;
	l_status = exec_ebt(ms, ebt->left);
	if (l_status == SUCCESS)
		r_status = exec_ebt(ms, ebt->right);
	return (l_status && r_status);
}

int	handle_or(t_minishell *ms, t_ebt *ebt)
{
	int	l_status;
	int	r_status;

	l_status = SUCCESS;
	r_status = SUCCESS;
	l_status = exec_ebt(ms, ebt->left);
	if (l_status == FAILURE)
		r_status = exec_ebt(ms, ebt->right);
	return (l_status || r_status);
}

int	handle_semicolon(t_minishell *ms, t_ebt *ebt)
{
	int	r_status;

	r_status = SUCCESS;
	exec_ebt(ms, ebt->left);
	r_status = exec_ebt(ms, ebt->right);
	return (r_status);
}

int	exec_ebt(t_minishell *ms, t_ebt *ebt)
{
	if (!ebt)
		return (FAILURE);
	if (ebt->type == EBT_OP_COMMAND)
		return (fork_and_exec(ms, ebt->command));
	else if (ebt->type == EBT_OP_PIPE)
		return (exec_pipe(ms, ebt->left, ebt->right));
	else if (ebt->type == EBT_OP_AND)
		return (handle_and(ms, ebt));
	else if (ebt->type == EBT_OP_OR)
		return (handle_or(ms, ebt));
	else if (ebt->type == EBT_OP_SEMICOLON)
		return (handle_semicolon(ms, ebt));
	else if (ebt->type == EBT_OP_SUBSHELL)
		return (exec_ebt(ms, ebt->left));
	else
	{
		ft_putstr_fd("Unsupported operation\n", STDERR_FILENO);
		return (FAILURE);
	}
}

void	executor(t_minishell *ms)
{
	t_ebt	*ebt;

	ebt = ms->ebt;
	exec_ebt(ms, ebt);
	return ;
}
