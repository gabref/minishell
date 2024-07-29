/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:43:55 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/25 14:09:44 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/utils.h"

static void	append_env_node(t_list **env_list, char *key, char *value)
{
	t_env	*env;
	t_list	*node;

	env = (t_env *)safe_malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	if (!env->key)
		free(env);
	env->value = ft_strdup(value);
	if (!env->value)
	{
		free(env->key);
		free(env);
	}
	node = ft_lstnew(env);
	if (!node)
	{
		free(env->key);
		free(env->value);
		free(env);
	}
	ft_lstadd_back(env_list, node);
}

int	ms_set_env(t_minishell *ms, char *key, char *value)
{
	t_list	*node;
	t_env	*env;

	node = ms->env;
	while (node)
	{
		env = (t_env *)node->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				return (1);
			return (0);
		}
		node = node->next;
	}
	append_env_node(&ms->env, key, value);
	return (0);
}

char	*ms_get_env(t_minishell *ms, char *key)
{
	t_list	*node;
	t_env	*env;

	node = ms->env;
	while (node)
	{
		env = (t_env *)node->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			return (ft_strdup(env->value));
		node = node->next;
	}
	return (NULL);
}

void	print_envs(t_list *env)
{
	t_env	*env_s;

	while (env)
	{
		env_s = (t_env *)env->content;
		ft_printf("%s=%s\n", env_s->key, env_s->value);
		env = env->next;
	}
}
