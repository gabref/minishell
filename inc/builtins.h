#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

void	builtin_cd(t_minishell *ms, char **args);
void	builtin_env(t_minishell *ms, char **args);
void	builtin_pwd(t_minishell *ms, char **args);
void	builtin_echo(t_minishell *ms, char **args);
void	builtin_exit(t_minishell *ms, char **args);
void	builtin_unset(t_minishell *ms, char **args);
void	builtin_clear(t_minishell *ms, char **args);
void	builtin_export(t_minishell *ms, char **args);

bool	is_builtin(char *command);
void	execute_builtin(t_minishell *ms, t_command *command);

/* cd helper functions */

char	*resolve_oldpwd(t_minishell *ms);
char	*resolve_home(t_minishell *ms);
char	*resolve_new_path(t_minishell *ms, char **args);

#endif
