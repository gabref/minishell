#include "../../../inc/builtins.h"

int	handle_too_many_arguments(t_minishell *ms, char **args)
{
	if (args && args[0] && args[1])
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		ms->last_exit_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	handle_special_characters(t_minishell *ms, char *arg)
{
	if (ft_strchr(arg, '+'))
	{
		ms->exit_ms = 100;
		return (FAILURE);
	}
	if (ft_strchr(arg, '-'))
	{
		ms->exit_ms = 156;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	handle_numeric_argument(t_minishell *ms, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
			ms->exit_ms = 2;
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	builtin_exit(t_minishell *ms, char **args)
{
	if (handle_too_many_arguments(ms, args) == FAILURE)
		return ;
	if (args && args[0])
	{
		if (handle_special_characters(ms, args[0]) == FAILURE)
			return ;
		if (handle_numeric_argument(ms, args[0]) == FAILURE)
			return ;
		ms->exit_ms = ft_atoi(args[0]);
		return ;
	}
	ms->exit_ms = ms->last_exit_status;
}
