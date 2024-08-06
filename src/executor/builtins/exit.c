#include "../../../inc/builtins.h"

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
