/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:47:43 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/30 02:39:21 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/utils.h"

void	print_token(t_token *token);

void	substitute_str(char **str, int start, int end, char *sub)
{
	char	*newstr;
	int		str_len;
	int		sub_len;
	int		i;
	int		newstr_len;
	int		j;

	str_len = ft_strlen(*str);
	sub_len = ft_strlen(sub);
	newstr_len = str_len - (end - start) + sub_len;
	newstr = safe_malloc(sizeof(char) * newstr_len + 1);
	i = -1;
	while (++i < start)
		newstr[i] = (*str)[i];
	j = 0;
	while (i < start + sub_len)
		newstr[i++] = sub[j++];
	while (i < newstr_len)
		newstr[i++] = (*str)[end++];
	newstr[i] = '\0';
	free(*str);
	*str = newstr;
}

void	substitute_envs(t_minishell *ms, char **value)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (*((*value) + i))
	{
		if ((*value)[i] == '$')
		{
			if (i > 0 && (*value)[i - 1] == '\\')
			{
				i++;
				continue ;
			}
			j = 0;
			while (ft_isalnum((*value)[i + j + 1]))
				j++;
			env = ms_get_env(ms, (*value) + i + 1);
			if (env == NULL)
				env = ft_strdup("");
			substitute_str(value, i, i + j + 1, env);
			free(env);
			i = -1;
		}
		i++;
	}
}

t_lexer	*expander(t_minishell *ms, t_lexer *lex)
{
	t_list	*node;

	node = lex->tokens;
	while (node)
	{
		if (((t_token *)node->content)->type == EXIT_STATUS)
		{
			free(((t_token *)node->content)->value);
			((t_token *)node->content)->type = WORD;
			((t_token *)node->content)->value = ft_itoa(ms->last_exit_status);
		}
		if (((t_token *)node->content)->type != WORD
			&& ((t_token *)node->content)->type != DOLLAR)
		{
			node = node->next;
			continue ;
		}
		if (((t_token *)node->content)->value
			&& ((t_token *)node->content)->value[0] == '\'')
		{
			node = node->next;
			if (node && ((t_token *)node->content)->value
				&& ((t_token *)node->content)->value[0] == '$')
				node = node->next;
			continue ;
		}
		if (ft_strchr(((t_token *)node->content)->value, '$'))
			substitute_envs(ms, &((t_token *)node->content)->value);
		node = node->next;
	}
	return (lex);
}
