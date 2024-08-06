/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:52:36 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 11:54:26 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	create_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

bool	is_end_of_heredoc(char *line, char *heredoc_word)
{
	size_t	len;

	len = ft_strlen(line);
	return (ft_strncmp(line, heredoc_word, len - 1) == 0 && line[len
			- 1] == '\n');
}

void	write_to_pipe(int write_fd, char *str)
{
	write(write_fd, str, ft_strlen(str));
}

char	*handle_heredoc(t_command *command)
{
	int		pipe_fd[2];
	char	*line;
	char	*heredoc_input;

	if (create_pipe(pipe_fd) == FAILURE)
		return (NULL);
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (is_end_of_heredoc(line, command->heredoc_word))
		{
			free(line);
			break ;
		}
		write_to_pipe(pipe_fd[1], line);
		free(line);
	}
	close(pipe_fd[1]);
	heredoc_input = read_file_to_string(pipe_fd[0]);
	close(pipe_fd[0]);
	return (heredoc_input);
}
