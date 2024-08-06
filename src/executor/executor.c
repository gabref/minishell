#include "../../inc/glob.h"
#include "../../inc/initializers.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include "../../inc/executor.h"
#include "../../inc/builtins.h"

int				exec_ebt(t_minishell *ms, t_ebt *ebt);

void	exec_command(t_minishell *ms, t_command *command, t_list *envs)
{
	char	*cmd_path;
	char	**envs_arr;
	int		exit_code;

	exit_code = 0;
	if (!command)
		exit(1);
	if (handle_redirections(ms, command) == FAILURE)
	{
		exit(1);
	}
	if (!command->command)
	{
		exit(0);
	}
	cmd_path = get_path_for_executable(ms, command->command, &exit_code);
	if (!cmd_path)
	{
		exit(exit_code);
	}
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
	{
		if (WEXITSTATUS(status) != 0)
			ms->last_exit_status = WEXITSTATUS(status);
	}
}

int	fork_and_exec(t_minishell *ms, t_command *command)
{
	pid_t	pid;

	if (!command)
		return (FAILURE);
	ms->last_exit_status = 0;
	save_redirection_state(ms);
	command->args = expand_wildcard(command->args);
	if (is_builtin(command->command))
		execute_builtin(ms, command);
	else
	{
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
	}
	restore_redirection_state(ms);
	if (ms->last_exit_status != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	exec_pipe(t_minishell *ms, t_ebt *left, t_ebt *right)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
		return (FAILURE);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		ft_putstr_fd("Error forking process\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_ebt(ms, left);
		exit(0);
	}
	waitpid(pid1, &status1, 0);
	pid2 = fork();
	if (pid2 < 0)
	{
		ft_putstr_fd("Error forking process\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exec_ebt(ms, right);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status1) && WIFEXITED(status2))
	{
		if (WEXITSTATUS(status1) != 0 || WEXITSTATUS(status2) != 0)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	exec_ebt(t_minishell *ms, t_ebt *ebt)
{
	int	l_status;
	int	r_status;

	if (!ebt)
		return (FAILURE);
	l_status = SUCCESS;
	r_status = SUCCESS;
	if (ebt->type == EBT_OP_COMMAND)
		l_status = fork_and_exec(ms, ebt->command);
	else if (ebt->type == EBT_OP_PIPE)
		l_status = exec_pipe(ms, ebt->left, ebt->right);
	else if (ebt->type == EBT_OP_AND)
	{
		l_status = exec_ebt(ms, ebt->left);
		if (l_status == SUCCESS)
			r_status = exec_ebt(ms, ebt->right);
	}
	else if (ebt->type == EBT_OP_OR)
	{
		l_status = exec_ebt(ms, ebt->left);
		if (l_status == FAILURE)
			r_status = exec_ebt(ms, ebt->right);
	}
	else if (ebt->type == EBT_OP_SEMICOLON)
	{
		l_status = exec_ebt(ms, ebt->left);
		r_status = exec_ebt(ms, ebt->right);
	}
	else if (ebt->type == EBT_OP_SUBSHELL)
		l_status = exec_ebt(ms, ebt->left);
	else
	{
		ft_putstr_fd("Unsupported operation\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (ebt->type == EBT_OP_AND)
		return (l_status && r_status);
	else if (ebt->type == EBT_OP_OR)
		return (l_status || r_status);
	else if (ebt->type == EBT_OP_PIPE)
		return (r_status);
	return (l_status);
}

void	executor(t_minishell *ms)
{
	t_ebt	*ebt;

	ebt = ms->ebt;
	exec_ebt(ms, ebt);
	return ;
}
