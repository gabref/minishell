/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:47:43 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/01 13:11:48 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/utils.h"

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
			while (ft_isalnum((*value)[i + j + 1]) || (*value)[i + j + 1] == '_'
				|| (*value)[i + j + 1] == '?')
				j++;
			if (j == 0)
			{
				i++;
				continue ;
			}
			if (j == 1 && (*value)[i + 1] == '?')
			{
				substitute_str(value, i, i + 2, ft_itoa(ms->last_exit_status));
				i = 0;
				continue ;
			}
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

void	handle_around_single_quotes(char **str)
{
	if ((*str)[0] == '\'')
		substitute_str(str, 0, 1, "");
	if ((*str)[ft_strlen(*str) - 1] == '\'')
		substitute_str(str, ft_strlen(*str) - 1, ft_strlen(*str), "");
}

void	handle_around_double_quotes(char **str)
{
	if ((*str)[0] == '\"')
		substitute_str(str, 0, 1, "");
	if ((*str)[ft_strlen(*str) - 1] == '\"' && (*str)[ft_strlen(*str)
		- 2] != '\\')
		substitute_str(str, ft_strlen(*str) - 1, ft_strlen(*str), "");
}

void	handle_quotes(char **str)
{
	int	i;
	int	start;

	start = 0;
	if ((*str)[0] == '"')
		start = 1;
	i = start;
	while ((*str)[i])
	{
		if ((!start && (*str)[i] == '\'') || (*str)[i] == '\"')
		{
			substitute_str(str, i, i + 1, "");
			i = start;
			continue ;
		}
		else if ((*str)[i] == '\\' && ((*str)[i + 1] == '\'' || (*str)[i
				+ 1] == '"'))
		{
			substitute_str(str, i, i + 2, "");
			i = start;
			continue ;
		}
		i++;
	}
}

const char	*get_escape_chars(void)
{
	static const char	escape_chars[] = {'\\', '\?', '\a', '\b', '\f', '\n',
			'\r', '\t', '\v'};

	return (escape_chars);
}

const char	**get_escape_strings(void)
{
	static const char	*escape_chars[] = {"\\", "?", "a", "b", "f", "n", "r",
			"t", "v"};

	return (escape_chars);
}

void	substitute_escape_chars(char **str)
{
	int		i;
	int		idx;
	char	*sub;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
		{
			idx = find_string_2d_array((*str + i + 1),
					(char **)get_escape_strings());
			if (idx != -1)
			{
				sub = ft_char_to_string(get_escape_chars()[idx]);
				substitute_str(str, i, i + 2, sub);
				free(sub);
			}
		}
		i++;
	}
}

void	handle_escape_chars(char **str)
{
	const char	*escape_chars = get_escape_chars();
	int			i;
	int			j;
	char		*newstr;
	int			str_len;
	int			newstr_len;

	i = 0;
	j = 0;
	str_len = ft_strlen(*str);
	newstr_len = str_len;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
		{
			if (ft_strchr(escape_chars, (*str)[i + 1]))
			{
				newstr_len--;
				i++;
			}
		}
		i++;
	}
	newstr = safe_malloc(sizeof(char) * newstr_len + 1);
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
		{
			if (ft_strchr(escape_chars, (*str)[i + 1]))
			{
				i++;
			}
		}
		newstr[j++] = (*str)[i++];
	}
	newstr[j] = '\0';
	free(*str);
	*str = newstr;
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
			handle_around_single_quotes(&((t_token *)node->content)->value);
			node = node->next;
			if (node && ((t_token *)node->content)->value
				&& ((t_token *)node->content)->value[0] == '$')
				node = node->next;
			continue ;
		}
		if (ft_strchr(((t_token *)node->content)->value, '$'))
			substitute_envs(ms, &((t_token *)node->content)->value);
		substitute_escape_chars(&((t_token *)node->content)->value);
		handle_escape_chars(&((t_token *)node->content)->value);
		handle_quotes(&((t_token *)node->content)->value);
		handle_around_double_quotes(&((t_token *)node->content)->value);
		node = node->next;
	}
	return (lex);
}
