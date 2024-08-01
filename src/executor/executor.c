#include "../../inc/initializers.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int				exec_ebt(t_minishell *ms, t_ebt *ebt);

int	find_string_2d_array(char *str, char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (-1);
	while (arr && arr[i])
	{
		if (ft_strncmp(str, arr[i], ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	builtin_echo(t_minishell *ms, char **args)
{
	bool	newline;
	int		i;

	(void)ms;
	newline = true;
	i = 0;
	if (find_string_2d_array("-n", args) == 0)
		newline = false;
	while (args && args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	builtin_cd(t_minishell *ms, char **args)
{
	char		*new_path;
	struct stat	path_stat;
	char		*old_path;

	new_path = NULL;
	if (args && args[0] && args[1])
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return ;
	}
	if (args != NULL && args[0] != NULL)
		new_path = args[0];
	if (new_path == NULL)
	{
		new_path = ms_get_env(ms, "HOME");
		if (!new_path)
		{
			ft_putstr_fd("no HOME env variable set\n", STDERR_FILENO);
			return ;
		}
	}
	else if (ft_strncmp(new_path, "~", 1) == 0)
	{
		new_path = ms_get_env(ms, "HOME");
		if (!new_path)
		{
			ft_putstr_fd("no HOME env variable set\n", STDERR_FILENO);
			return ;
		}
	}
	else if (ft_strncmp(new_path, "-", 1) == 0)
	{
		new_path = ms_get_env(ms, "OLDPWD");
		if (!new_path)
		{
			ft_putstr_fd("no OLDPWD env variable set\n", STDERR_FILENO);
			return ;
		}
	}
	else
		new_path = ft_strdup(new_path);
	if (stat(new_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode) == 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		ms->last_exit_status = 1;
		free(new_path);
		return ;
	}
	if (chdir(new_path) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		ms->last_exit_status = 1;
		free(new_path);
		return ;
	}
	free(new_path);
	new_path = getcwd(NULL, PATH_MAX);
	if (new_path == NULL)
	{
		return ;
	}
	old_path = ms_get_env(ms, "PWD");
	ms_set_env(ms, "OLDPATH", old_path);
	ms_set_env(ms, "PWD", new_path);
	free(old_path);
	free(new_path);
}

void	builtin_pwd(t_minishell *ms, char **args)
{
	char	*pwd;

	(void)args;
	pwd = ms_get_env(ms, "PWD");
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
}

void ms_remove_env(t_minishell *ms, char *key)
{
	t_list	*node;
	t_list	*prev;
	t_env	*env;

	node = ms->env;
	prev = NULL;
	while (node)
	{
		env = (t_env *)node->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			if (prev == NULL)
				ms->env = node->next;
			else
				prev->next = node->next;
			free(env->key);
			free(env->value);
			free(env);
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

void	builtin_unset(t_minishell *ms, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		ms_remove_env(ms, args[i]);
		i++;
	}
}

void	builtin_env(t_minishell *ms, char **args)
{
	(void)args;
	print_envs(ms->env);
}

void	builtin_export(t_minishell *ms, char **args)
{
	char	**splitted;

	if (!args || !args[0])
	{
		builtin_env(ms, args);
		return ;
	}
	if (args && args[0] && args[1])
		return ;
	if (ft_strchr(args[0], '-') || !ft_isalpha(args[0][0]) || args[0][0] == '=')
	{
		ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return ;
	}
	if (ft_strchr(args[0], '='))
	{
		splitted = ft_split(args[0], '=');
		if (splitted && splitted[0] && splitted[1])
			ms_set_env(ms, splitted[0], splitted[1]);
		ft_free_2d_array((void **)splitted);
	}
}

void	builtin_exit(t_minishell *ms, char **args)
{
	int	i;

	i = 0;
	if (args && args[0] && args[1])
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return ;
	}
	if (args && args[0])
	{
		if (ft_strchr(args[0], '+'))
		{
			ms->exit_ms = 100;
			return ;
		}
		if (ft_strchr(args[0], '-'))
		{
			ms->exit_ms = 156;
			return ;
		}
		while (args[0][i])
		{
			if (!ft_isdigit(args[0][i]))
			{
				ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
				ms->exit_ms = 2;
				return ;
			}
			i++;
		}
		ms->exit_ms = ft_atoi(args[0]);
		return ;
	}
	ms->exit_ms = ms->last_exit_status;
}

const t_builtin	*get_builtins(void)
{
	static const t_builtin	builtins[] = {{"echo", builtin_echo}, {"cd",
			builtin_cd}, {"pwd", builtin_pwd}, {"export", builtin_export},
			{"unset", builtin_unset}, {"env", builtin_env}, {"exit",
			builtin_exit}, {NULL, NULL}};

	return (builtins);
}

bool	is_builtin(char *command)
{
	const t_builtin	*builtins;
	int				i;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(command, builtins[i].name, ft_strlen(command)) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	execute_builtin(t_minishell *ms, t_command *command)
{
	const t_builtin	*builtins;
	int				i;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(command->command, builtins[i].name,
				ft_strlen(command->command)) == 0)
		{
			builtins[i].builtin_func(ms, command->args);
			return ;
		}
		i++;
	}
	ft_putstr_fd("Unknown builtin command\n", STDOUT_FILENO);
}

char	*get_path_for_executable(t_minishell *ms, char *command)
{
	char	*path;
	char	*path_env;
	char	*cmd_path;
	char	**path_dirs;
	int		i;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
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
				ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
				ms->last_exit_status = 1;
				return (FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir_node = redir_node->next;
	}
	return (SUCCESS);
}

void	exec_command(t_minishell *ms, t_command *command, t_list *envs)
{
	char	*cmd_path;
	char	**envs_arr;

	if (!command || !command->command)
		exit(1);
	if (handle_redirections(ms, command) == FAILURE)
	{
		exit(1);
	}
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
			ms->last_exit_status = WEXITSTATUS(status);
		}
	}
}

int	fork_and_exec(t_minishell *ms, t_command *command)
{
	pid_t	pid;

	if (!command || !command->command)
		return (FAILURE);
	if (is_builtin(command->command))
	{
		execute_builtin(ms, command);
		if (ms->last_exit_status != 0)
			return (FAILURE);
		return (SUCCESS);
	}
	save_redirection_state(ms);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error forking process\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (pid == 0)
		exec_command(ms, command, ms->env);
	else
		exec_parent(ms, pid, command->command);
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
