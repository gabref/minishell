#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define PERMISSION_CHECK_ERROR 2
# define FILE_NOT_FOUND_ERROR 1
# define PERMISSIONS_OK 0

void	executor(t_minishell *ms);

int		exec_ebt(t_minishell *ms, t_ebt *ebt);
int		fork_and_exec(t_minishell *ms, t_command *command);
int		exec_pipe(t_minishell *ms, t_ebt *left, t_ebt *right);

int		check_file_permissions(const char *filepath, int flags);
int		is_directory(char *command);
char	**get_envs(t_list *envs);
char	*read_file_to_string(int fd);
char	*get_path_for_executable(t_minishell *ms, char *command,
			int *exit_code);

void	save_redirection_state(t_minishell *ms);
void	restore_redirection_state(t_minishell *ms);
char	*handle_heredoc(t_command *command);
int		handle_redirections(t_minishell *ms, t_command *command);

char	*handle_heredoc(t_command *command);

int		handle_heredoc_command(t_minishell *ms, t_command *command);
int		open_redirection_file(t_minishell *ms, char *filename, int flags);

#endif
