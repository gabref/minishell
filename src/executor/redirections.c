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

int	handle_redirections(t_minishell *ms, t_command *command)
{
	t_list	*redir_node;
	t_redir	*redir;
	int		flags;
	int		fd;
	char	*heredoc_input;

	heredoc_input = NULL;
	if (command->heredoc)
	{
		heredoc_input = handle_heredoc(command);
		if (!heredoc_input)
		{
			ms->last_exit_status = 1;
			return (FAILURE);
		}
		if (command->redirections)
		{
			redir_node = command->redirections;
			while (redir_node)
			{
				redir = (t_redir *)redir_node->content;
				if (redir->to == RT_WRITE || redir->to == RT_APPEND)
				{
					flags = O_WRONLY | O_CREAT;
					if (redir->to == RT_APPEND)
						flags |= O_APPEND;
					fd = open(redir->filename, flags, 0644);
					if (fd < 0)
					{
						if (check_file_permissions(redir->filename,
								W_OK) == PERMISSION_CHECK_ERROR)
							ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
						else if (check_file_permissions(redir->filename,
								W_OK) == FILE_NOT_FOUND_ERROR)
							ft_putstr_fd(" No such file or directory\n",
								STDERR_FILENO);
						else
							ft_putstr_fd("Error opening file\n", STDERR_FILENO);
						free(heredoc_input);
						return (FAILURE);
					}
					write(fd, heredoc_input, ft_strlen(heredoc_input));
					close(fd);
				}
				redir_node = redir_node->next;
			}
			free(heredoc_input);
			heredoc_input = NULL;
		}
		else
		{
			ft_putstr_fd(heredoc_input, STDOUT_FILENO);
			free(heredoc_input);
		}
	}
	redir_node = command->redirections;
	while (redir_node)
	{
		redir = (t_redir *)redir_node->content;
		if (redir->to == RT_WRITE || redir->to == RT_APPEND)
		{
			flags = O_WRONLY | O_CREAT;
			if (redir->to == RT_APPEND)
				flags |= O_APPEND;
			fd = open(redir->filename, flags, 0644);
			if (fd < 0)
			{
				if (check_file_permissions(redir->filename,
						W_OK) == PERMISSION_CHECK_ERROR)
					ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
				else if (check_file_permissions(redir->filename,
						W_OK) == FILE_NOT_FOUND_ERROR)
					ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
				else
					ft_putstr_fd("Error opening file\n", STDERR_FILENO);
				return (FAILURE);
			}
			if (redir->from == RT_STDOUT)
				dup2(fd, STDOUT_FILENO);
			else if (redir->from == RT_STDERR)
				dup2(fd, STDERR_FILENO);
			close(fd);
		}
		else if (redir->to == RT_READ)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0)
			{
				if (check_file_permissions(redir->filename,
						R_OK) == PERMISSION_CHECK_ERROR)
					ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
				else if (check_file_permissions(redir->filename,
						R_OK) == FILE_NOT_FOUND_ERROR)
					ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
				else
					ft_putstr_fd("Error opening file\n", STDERR_FILENO);
				ms->last_exit_status = 1;
				return (FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir_node = redir_node->next;
	}
	if (!command->heredoc)
		free(heredoc_input);
	return (SUCCESS);
}

