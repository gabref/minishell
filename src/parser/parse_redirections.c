/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:10:10 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 20:20:55 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

static bool	set_redir_value(t_redir *redir, t_list **tokens, int from, int to)
{
	t_token	*token;

	token = eat(tokens);
	if (token == NULL || token->value == NULL)
		return (false);
	redir->from = from;
	redir->to = to;
	redir->filename = ft_strdup(token->value);
	return (true);
}

static t_redir_map	*get_redir_map(int token_type)
{
	static const t_redir_map	redir_map[] = {{O_ANGLE_BRACKET, RT_STDIN,
			RT_READ, "<"}, {C_ANGLE_BRACKET, RT_STDOUT, RT_WRITE, ">"},
			{C_DANGLE_BRACKET, RT_STDOUT, RT_APPEND, ">>"}, {0, 0, 0, NULL}};
	int							i;

	i = 0;
	while (redir_map[i].token_type != 0)
	{
		if (redir_map[i].token_type == token_type)
			return ((t_redir_map *)&redir_map[i]);
		i++;
	}
	return (NULL);
}

bool	handle_double_angle_bracket(t_minishell *ms, t_command *command,
		t_redir *redir, t_list **tokens)
{
	t_token	*token;

	command->heredoc = true;
	token = eat(tokens);
	if (token == NULL || token->value == NULL)
		return (handle_error_redir(ms, command, redir, "<<"));
	command->heredoc_word = ft_strdup(token->value);
	free(redir);
	return (true);
}

bool	parser_handle_redirections(t_minishell *ms, t_command *command,
		t_list **tokens)
{
	t_token		*token;
	t_redir		*redir;
	t_redir_map	*redir_map;

	if (!is_angle_bracket(peek(*tokens)))
		return (true);
	token = eat(tokens);
	redir = create_redir();
	if (token->type == O_DANGLE_BRACKET)
		return (handle_double_angle_bracket(ms, command, redir, tokens));
	else
	{
		redir_map = get_redir_map(token->type);
		if (redir_map == NULL || !set_redir_value(redir, tokens,
				redir_map->from, redir_map->to))
			return (handle_error_redir(ms, command, redir,
					redir_map->error_char));
	}
	if (command->redirections == NULL)
		command->redirections = ft_lstnew(redir);
	else
		ft_lstadd_back(&command->redirections, ft_lstnew(redir));
	return (true);
}

bool	handle_angle_bracket_first_token(t_minishell *ms, t_command *command,
		t_list **tokens, t_token *token)
{
	t_redir	*redir;

	if (token->type == O_ANGLE_BRACKET || token->type == C_DANGLE_BRACKET)
		handle_error_command(ms, command, "Error: unexpected token",
			token->value);
	else if (token->type == O_DANGLE_BRACKET)
	{
		token = eat(tokens);
		command->heredoc = true;
		if (token != NULL && token->type == WORD)
			command->heredoc_word = ft_strdup(token->value);
		else
			return (handle_error_command(ms, command,
					"Error: expected command after", "'<<'"));
	}
	else if (token->type == C_ANGLE_BRACKET)
	{
		redir = create_redir();
		if (!set_redir_value(redir, tokens, RT_STDOUT, RT_WRITE))
			return (handle_error_redir(ms, command, redir, ">"));
		command->redirections = ft_lstnew(redir);
	}
	return (true);
}
