/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:40:10 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 11:41:40 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/glob.h"
#include "../../inc/initializers.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include "../../inc/executor.h"
#include "../../inc/minishell.h"

void	exec_command(t_minishell *ms, t_command *command, t_list *envs)
{
	char	*cmd_path;
	char	**envs_arr;
	int		exit_code;

	exit_code = 0;
	if (!command)
		exit(1);
	if (handle_redirections(ms, command) == FAILURE)
		exit(1);
	if (!command->command)
		exit(0);
	cmd_path = get_path_for_executable(ms, command->command, &exit_code);
	if (!cmd_path)
		exit(exit_code);
	envs_arr = get_envs(envs);
	add_string_front(&command->args, cmd_path);
	execve(cmd_path, command->args, envs_arr);
	ft_free_2d_array((void **)envs_arr);
	if (envs != NULL)
		ft_lstclear(&envs, &destroy_env);
	free_command(command);
	destroy_minishell(ms);
	exit(-1);
}

void	exec_parent(t_minishell *ms, pid_t child_pid)
{
	int	status;

	if (waitpid(child_pid, &status, 0) < 0)
	{
		if (get_global_signal() == SIGINT)
		{
			ft_printf("\n");
			return ;
		}
		ft_putstr_fd("Error waiting for child process\n", STDERR_FILENO);
		return ;
	}
	if (WIFSIGNALED(status))
	{
		set_global_signal(WTERMSIG(status));
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		else
			printf("%s\n", strsignal(WTERMSIG(status)));
	}
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) != 0)
			ms->last_exit_status = WEXITSTATUS(status);
}

int	execute_command_in_fork(t_minishell *ms, t_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error forking process\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (pid == 0)
		exec_command(ms, command, ms->env);
	else
		exec_parent(ms, pid);
	return (SUCCESS);
}

int	fork_and_exec(t_minishell *ms, t_command *command)
{
	if (!command)
		return (FAILURE);
	ms->last_exit_status = 0;
	save_redirection_state(ms);
	command->args = expand_wildcard(command->args);
	if (is_builtin(command->command))
		execute_builtin(ms, command);
	else
		execute_command_in_fork(ms, command);
	restore_redirection_state(ms);
	if (ms->last_exit_status != 0)
		return (FAILURE);
	return (SUCCESS);
}
