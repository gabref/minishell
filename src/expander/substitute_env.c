/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:04:54 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 13:05:05 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/utils.h"

static void	substitute_env_variable(t_minishell *ms, char **value, int *i,
		int j)
{
	char	*env;

	env = ms_get_env(ms, (*value) + *i + 1);
	if (env == NULL)
		env = ft_strdup("");
	substitute_str(value, *i, *i + j + 1, env);
	free(env);
	*i = -1;
}

static void	substitute_exit_status(t_minishell *ms, char **value, int *i)
{
	char	*tmp;

	tmp = ft_itoa(ms->last_exit_status);
	substitute_str(value, *i, *i + 2, tmp);
	free(tmp);
	*i = 0;
}

static void	process_dollar_sign(t_minishell *ms, char **value, int *i)
{
	int	j;

	j = 0;
	if (*i > 0 && (*value)[*i - 1] == '\\')
	{
		(*i)++;
		return ;
	}
	j = 0;
	while (ft_isalnum((*value)[*i + j + 1]) || (*value)[*i + j + 1] == '_'
		|| (*value)[*i + j + 1] == '?')
	{
		if ((*value)[*i + j++ + 1] == '?')
			break ;
	}
	if (j == 0)
	{
		(*i)++;
		return ;
	}
	if (j == 1 && (*value)[*i + 1] == '?')
		substitute_exit_status(ms, value, i);
	else
		substitute_env_variable(ms, value, i, j);
}

void	substitute_envs(t_minishell *ms, char **value)
{
	int	i;

	i = 0;
	while (*((*value) + i))
	{
		if ((*value)[i] == '$')
		{
			process_dollar_sign(ms, value, &i);
		}
		i++;
	}
}
