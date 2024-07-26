/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:47:43 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/26 07:25:00 by galves-f         ###   ########.fr       */
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
	t_token	*token;

	token = lex->tokens;
	while (token)
	{
		if (token->type != WORD && token->type != DOLLAR)
		{
			token = token->next;
			continue ;
		}
		if (token->value && token->value[0] == '\'')
		{
			token = token->next;
			if (token && token->value && token->value[0] == '$')
				token = token->next;
			continue ;
		}
		if (ft_strchr(token->value, '$'))
			substitute_envs(ms, &token->value);
		token = token->next;
	}
	return (lex);
}
