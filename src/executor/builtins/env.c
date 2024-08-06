#include "../../../inc/builtins.h"

void	builtin_env(t_minishell *ms, char **args)
{
	(void)args;
	print_envs(ms->env);
}
