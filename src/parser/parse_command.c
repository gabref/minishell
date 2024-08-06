#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"

t_command	*handle_initial_token(t_minishell *ms, t_list **tokens,
		t_token *token)
{
	t_command	*command;

	command = create_command();
	if (token->type == WORD)
		command->command = ft_strdup(token->value);
	else if (!handle_angle_bracket_first_token(ms, command, tokens, token))
		return (NULL);
	return (command);
}

bool process_inner_tokens(t_minishell *ms, t_command *command, t_list **tokens)
{
	t_token *token;

	while (is_primary_token(peek(*tokens)))
	{
		if (is_angle_bracket(peek(*tokens)))
		{
			if (!parser_handle_redirections(ms, command, tokens))
				return (false);
		}
		else if (peek(*tokens)->type == BSLASH)
		{
			token = eat(tokens);
			continue ;
		}
		else if (peek(*tokens)->type == CMD_SUB)
		{
			handle_error_command(ms, command,
				"Error: command substitution not available", "");
			return (false);
		}
		else
		{
			token = eat(tokens);
			add_string(&command->args, ft_strdup(token->value));
		}
	}
	return (true);
}

t_ebt	*parse_word_or_angle(t_minishell *ms, t_list **tokens)
{
	t_token		*token;
	t_command	*command;
	t_ebt		*ebt;

	token = eat(tokens);
	command = handle_initial_token(ms, tokens, token);
	if (command == NULL)
		return (NULL);
	if (!process_inner_tokens(ms, command, tokens))
	{
		free_command(command);
		return (NULL);
	}
	ebt = create_ebt();
	ebt->command = command;
	return (ebt);
}

t_ebt	*parse_command(t_minishell *ms, t_list **tokens)
{
	t_token		*token;
	t_ebt		*ebt;

	token = peek(*tokens);
	ebt = NULL;
	if (token == NULL || is_close_parenthesis(token))
		return (handle_error(ms, "Error: unexpected end of command"));
	if (token->type != WORD && !is_open_parenthesis(token)
		&& !is_angle_bracket(token))
		return (handle_error(ms, "parse error: unexpected token"));
	else if (token->type == WORD || is_angle_bracket(token))
		return (parse_word_or_angle(ms, tokens));
	else if (is_open_parenthesis(token))
		return (parse_parenthesis(ms, tokens, token));
	return (ebt);
}
