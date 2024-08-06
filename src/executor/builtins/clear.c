#include "../../../inc/builtins.h"

void	builtin_clear(t_minishell *ms, char **args)
{
	(void)args;
	(void)ms;
	write(STDOUT_FILENO, "\033[H\033[J", 6);
}
