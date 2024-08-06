/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:45:16 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 11:49:34 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/minishell.h"

static int	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error forking process\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (pid);
}

static void	exec_child_process(t_minishell *ms, t_ebt *cmd, int *pipe_fd,
		int std_fd)
{
	close(pipe_fd[1 - std_fd]);
	dup2(pipe_fd[std_fd], std_fd);
	close(pipe_fd[std_fd]);
	exec_ebt(ms, cmd);
	exit(0);
}

static int	handle_child_process(t_minishell *ms, t_ebt *cmd, int *pipe_fd,
		int std_fd)
{
	pid_t	pid;

	pid = fork_process();
	if (pid == 0)
		exec_child_process(ms, cmd, pipe_fd, std_fd);
	else if (pid < 0)
		return (FAILURE);
	return (pid);
}

static int	close_pipe_and_wait(int *pipe_fd, pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status1) && WIFEXITED(status2))
		if (WEXITSTATUS(status1) != 0 || WEXITSTATUS(status2) != 0)
			return (FAILURE);
	return (SUCCESS);
}

int	exec_pipe(t_minishell *ms, t_ebt *left, t_ebt *right)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
		return (FAILURE);
	}
	pid1 = handle_child_process(ms, left, pipe_fd, STDOUT_FILENO);
	if (pid1 == FAILURE)
		return (FAILURE);
	pid2 = handle_child_process(ms, right, pipe_fd, STDIN_FILENO);
	if (pid2 == FAILURE)
		return (FAILURE);
	return (close_pipe_and_wait(pipe_fd, pid1, pid2));
}
