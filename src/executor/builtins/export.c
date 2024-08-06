#include "../../../inc/builtins.h"

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
