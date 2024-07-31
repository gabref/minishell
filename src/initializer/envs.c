/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:57:52 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/31 14:02:38 by galves-f         ###   ########.fr       */
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
	if (env == NULL)
		return (NULL);
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

static char	*default_env_value(char *key)
{
	int		i;
	t_env	env_mapping[7];

	env_mapping[0] = (t_env){.key = "SHLVL", .value = "1"};
	env_mapping[1] = (t_env){.key = "PWD", .value = "/"};
	env_mapping[2] = (t_env){.key = "OLDPWD", .value = "/"};
	env_mapping[3] = (t_env){.key = "HOME", .value = "/"};
	env_mapping[4] = (t_env){.key = "USER", .value = "default_user"};
	env_mapping[5] = (t_env){.key = "PATH",
		.value = "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin"};
	env_mapping[6] = (t_env){.key = "_", .value = "minishell"};
	i = -1;
	while (env_mapping[++i].key)
		if (ft_strncmp(key, env_mapping[i].key,
				ft_strlen(env_mapping[i].key)) == 0)
			return (ft_strdup(env_mapping[i].value));
	return (ft_strdup(""));
}

/*
TODO: when env is NULL, create a new env with the default values
*/
static t_list	*create_env_node(char *key, char **env)
{
	t_env	*env_s;
	t_list	*node;
	char	*value;

	env_s = (t_env *)safe_malloc(sizeof(t_env));
	value = get_env(key, env);
	if (value == NULL)
		env_s->value = default_env_value(key);
	else if (value != NULL && ft_strncmp(key, "SHLVL", 5) == 0)
		env_s->value = ft_itoa(ft_atoi(value) + 1);
	else
		env_s->value = ft_strdup(value);
	free(value);
	env_s->key = ft_strdup(key);
	if (!env_s->key)
		return (free(env_s), NULL);
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
