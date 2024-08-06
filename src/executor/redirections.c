/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:44:14 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 12:18:19 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	open_redirection_file(t_minishell *ms, char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		if (check_file_permissions(filename, W_OK) == PERMISSION_CHECK_ERROR)
			ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		else if (check_file_permissions(filename, W_OK) == FILE_NOT_FOUND_ERROR)
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		else
			ft_putstr_fd("Error opening file\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	handle_write_append_redirection(t_minishell *ms, t_redir *redir)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (redir->to == RT_APPEND)
		flags |= O_APPEND;
	fd = open_redirection_file(ms, redir->filename, flags);
	if (fd < 0)
		return (FAILURE);
	if (redir->from == RT_STDOUT)
		dup2(fd, STDOUT_FILENO);
	else if (redir->from == RT_STDERR)
		dup2(fd, STDERR_FILENO);
	close(fd);
	return (SUCCESS);
}

int	handle_read_redirection(t_minishell *ms, t_redir *redir)
{
	int	fd;

	fd = open_redirection_file(ms, redir->filename, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	handle_redirections(t_minishell *ms, t_command *command)
{
	t_list	*redir_node;
	t_redir	*redir;

	if (command->heredoc)
		if (handle_heredoc_command(ms, command) == FAILURE)
			return (FAILURE);
	redir_node = command->redirections;
	while (redir_node)
	{
		redir = (t_redir *)redir_node->content;
		if (redir->to == RT_WRITE || redir->to == RT_APPEND)
		{
			if (handle_write_append_redirection(ms, redir) == FAILURE)
				return (FAILURE);
		}
		else if (redir->to == RT_READ)
		{
			if (handle_read_redirection(ms, redir) == FAILURE)
				return (FAILURE);
		}
		redir_node = redir_node->next;
	}
	return (SUCCESS);
}
