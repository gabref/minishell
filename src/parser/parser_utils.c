/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:52:22 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 18:31:02 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	not_eof(t_token *token)
{
	return (token != NULL && token->type != END_OF_FILE);
}

t_token	*peek(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
		return (NULL);
	token = (t_token *)tokens->content;
	return (token);
}

t_token	*eat(t_list **tokens)
{
	t_token	*token;

	if (*tokens == NULL)
		return (NULL);
	token = (t_token *)(*tokens)->content;
	if (token == NULL)
		return (NULL);
	*tokens = (*tokens)->next;
	return (token);
}

void	*expect(t_minishell *ms, t_list **tokens, t_token_type type,
		char *err_message)
{
	t_token	*token;

	token = eat(tokens);
	if (!token)
	{
		if (ms->last_exit_status == 0)
			ft_printf(RED "Error: %s\n" RST, err_message);
		ms->last_exit_status = 1;
		return (NULL);
	}
	else if (token->type != type)
	{
		if (ms->last_exit_status == 0)
		{
			ft_printf(RED "Error: %s\n", err_message);
			ft_printf("got: %s\n" RST, token->value);
		}
		ms->last_exit_status = 1;
		return (NULL);
	}
	return (token);
}
