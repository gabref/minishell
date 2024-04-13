/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:57:52 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/13 16:21:45 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/initializers.h"
#include "../../inc/minishell.h"
#include "../../inc/utils.h"

static char	*get_env(char *var, char **env)
{
	int		i;
	char	**split_env;
	char	*env_name;
	char	*env_contents;

	i = 0;
	while (env[i])
	{
		split_env = ft_split(env[i++], '=');
		env_name = split_env[0];
		if (ft_strncmp(env_name, var, ft_strlen(env_name)) == 0)
		{
			env_contents = ft_strdup(split_env[1]);
			ft_free_2d_array((void **)split_env);
			return (env_contents);
		}
		ft_free_2d_array((void **)split_env);
	}
	return (NULL);
}

static t_list	*create_env_node(char *key, char **env)
{
	t_env	*env_s;
	t_list	*node;
	char	*value;

	env_s = (t_env *)safe_malloc(sizeof(t_env));
	env_s->key = ft_strdup(key);
	if (!env_s->key)
		return (free(env_s), NULL);
	value = get_env(key, env);
	env_s->value = value;
	if (ft_strncmp(key, "SHLVL", 5) == 0)
	{
		if (value == NULL)
			env_s->value = ft_strdup("1");
		else
			env_s->value = ft_itoa(ft_atoi(value) + 1);
		free(value);
	}
	node = ft_lstnew(env_s);
	if (!node)
		return (free(env_s->key), free(env_s), NULL);
	return (node);
}

static void	append_env_node(t_list **env_list, char *key, char **env)
{
	t_list	*node;

	node = create_env_node(key, env);
	if (node)
		ft_lstadd_back(env_list, node);
}

t_list	*get_env_list(char **env)
{
	t_list	*env_list;

	env_list = NULL;
	append_env_node(&env_list, "SHLVL", env);
	append_env_node(&env_list, "PWD", env);
	append_env_node(&env_list, "OLDPWD", env);
	append_env_node(&env_list, "HOME", env);
	append_env_node(&env_list, "USER", env);
	append_env_node(&env_list, "PATH", env);
	append_env_node(&env_list, "_", env);
	return (env_list);
}
