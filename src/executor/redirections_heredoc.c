/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:44:06 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 10:46:43 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	handle_heredoc_redirections(t_minishell *ms, t_list *r_node, char *h_input)
{
	t_redir	*redir;
	int		flags;
	int		fd;

	while (r_node)
	{
		redir = (t_redir *)r_node->content;
		if (redir->to == RT_WRITE || redir->to == RT_APPEND)
		{
			flags = O_WRONLY | O_CREAT;
			if (redir->to == RT_APPEND)
				flags |= O_APPEND;
			fd = open_redirection_file(ms, redir->filename, flags);
			if (fd < 0)
			{
				free(h_input);
				return (FAILURE);
			}
			write(fd, h_input, ft_strlen(h_input));
			close(fd);
		}
		r_node = r_node->next;
	}
	return (SUCCESS);
}

int	handle_heredoc_command(t_minishell *ms, t_command *command)
{
	char	*heredoc_input;

	heredoc_input = handle_heredoc(command);
	if (!heredoc_input)
	{
		ms->last_exit_status = 1;
		return (FAILURE);
	}
	if (command->redirections)
	{
		if (handle_heredoc_redirections(ms, command->redirections,
				heredoc_input) == FAILURE)
			return (FAILURE);
		free(heredoc_input);
		heredoc_input = NULL;
	}
	else
	{
		ft_putstr_fd(heredoc_input, STDOUT_FILENO);
		free(heredoc_input);
	}
	return (SUCCESS);
}
