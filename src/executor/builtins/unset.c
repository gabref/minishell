#include "../../../inc/builtins.h"

void	ms_remove_env(t_minishell *ms, char *key)
{
	t_list	*node;
	t_list	*prev;
	t_env	*env;

	node = ms->env;
	prev = NULL;
	while (node)
	{
		env = (t_env *)node->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			if (prev == NULL)
				ms->env = node->next;
			else
				prev->next = node->next;
			free(env->key);
			free(env->value);
			free(env);
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

void	builtin_unset(t_minishell *ms, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		ms_remove_env(ms, args[i]);
		i++;
	}
}
