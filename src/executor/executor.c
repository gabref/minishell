#include "../../inc/initializers.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int		exec_ebt(t_minishell *ms, t_ebt *ebt);

char	*get_path_for_executable(t_minishell *ms, char *command)
{
	char	*path;
	char	*path_env;
	char	*cmd_path;
	char	**path_dirs;
	int		i;

	path = NULL;
	path_env = ms_get_env(ms, "PATH");
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		path = ft_strjoin(path_dirs[i++], "/");
		cmd_path = ft_strjoin(path, command);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		free(path);
		free(cmd_path);
		cmd_path = NULL;
	}
	free(path_env);
	ft_free_2d_array((void **)path_dirs);
	return (cmd_path);
}

char	**get_envs(t_list *envs)
{
	char	**env;
	t_list	*node;
	t_env	*env_node;
	int		i;

	i = 0;
	node = envs;
	while (node)
	{
		i++;
		node = node->next;
	}
	env = safe_malloc(sizeof(char *) * (i + 1));
	i = 0;
	node = envs;
	while (node)
	{
		env_node = (t_env *)node->content;
		env[i] = ft_strjoin(env_node->key, "=");
		env[i] = ft_strjoin(env[i], env_node->value);
		node = node->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	exec_command(t_minishell *ms, t_command *command, t_list *envs)
{
	char	*cmd_path;
	char	**envs_arr;

	if (!command || !command->command)
		exit(-1);
	cmd_path = get_path_for_executable(ms, command->command);
	if (!cmd_path)
	{
		exit(127);
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

void	exec_parent(t_minishell *ms, pid_t child_pid, char *command)
{
	int	status;

	if (waitpid(child_pid, &status, 0) < 0)
	{
		ft_putstr_fd("Error waiting for child process\n", STDERR_FILENO);
		return ;
	}
	ms->last_exit_status = 0;
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
		{
			if (WEXITSTATUS(status) == 127)
				printf("command not found: %s\n", command);
			else
				printf("%s - %d\n", strerror(WEXITSTATUS(status)),
					ms->last_exit_status);
			ms->last_exit_status = WEXITSTATUS(status);
		}
	}
}

int	fork_and_exec(t_minishell *ms, t_command *command)
{
	pid_t	pid;

	if (!command || !command->command)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error forking process\n", STDERR_FILENO);
		return (-1);
	}
	if (pid == 0)
		exec_command(ms, command, ms->env);
	else
		exec_parent(ms, pid, command->command);
	if (ms->last_exit_status != 0)
		return (-1);
	return (0);
}

int	exec_pipe(t_minishell *ms, t_ebt *left, t_ebt *right, t_list *envs)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	(void)envs;
	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
		return (-1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		ft_putstr_fd("Error forking process\n", STDERR_FILENO);
		return (-1);
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
		return (-1);
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
			return (-1);
	}
	return (0);
}

int	exec_ebt(t_minishell *ms, t_ebt *ebt)
{
	int	l_status;
	int	r_status;

	if (!ebt)
		return (-1);
	l_status = 0;
	r_status = 0;
	if (ebt->type == EBT_OP_COMMAND)
		l_status = fork_and_exec(ms, ebt->command);
	else if (ebt->type == EBT_OP_PIPE)
		l_status = exec_pipe(ms, ebt->left, ebt->right, ms->env);
	else if (ebt->type == EBT_OP_AND)
	{
		l_status = exec_ebt(ms, ebt->left);
		if (l_status == 0)
			r_status = exec_ebt(ms, ebt->right);
	}
	else if (ebt->type == EBT_OP_OR)
	{
		l_status = exec_ebt(ms, ebt->left);
		if (l_status != 0)
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
		return (-1);
	}
	if (ebt->type == EBT_OP_AND || ebt->type == EBT_OP_OR)
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
