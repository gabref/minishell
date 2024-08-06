/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:47:43 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 13:35:44 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

static void	process_exit_status(t_minishell *ms, t_token *token)
{
	free(token->value);
	token->type = WORD;
	token->value = ft_itoa(ms->last_exit_status);
}

static void	process_substitutions_and_escape(t_minishell *ms, t_token *token)
{
	if (ft_strchr(token->value, '$'))
		substitute_envs(ms, &token->value);
	substitute_escape_chars(&token->value);
	handle_escape_chars(&token->value);
	handle_quotes(&token->value);
	handle_around_double_quotes(&token->value);
}

static int	skip_list(t_list **node)
{
	*node = (*node)->next;
	return (1);
}

t_lexer	*expander(t_minishell *ms, t_lexer *lex)
{
	t_list	*node;
	t_token	*token;

	node = lex->tokens;
	while (node)
	{
		token = (t_token *)node->content;
		if (token->type == EXIT_STATUS)
			process_exit_status(ms, token);
		if (token->type != WORD && token->type != DOLLAR && skip_list(&node))
			continue ;
		if (token->value && token->value[0] == '\'')
		{
			handle_around_single_quotes(&token->value);
			node = node->next;
			if (node && ((t_token *)node->content)->value
				&& ((t_token *)node->content)->value[0] == '$')
				node = node->next;
			continue ;
		}
		process_substitutions_and_escape(ms, (t_token *)node->content);
		node = node->next;
	}
	return (lex);
}
