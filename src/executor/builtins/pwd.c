#include "../../../inc/builtins.h"

void	builtin_pwd(t_minishell *ms, char **args)
{
	char	*pwd;

	(void)args;
	pwd = ms_get_env(ms, "PWD");
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
}
