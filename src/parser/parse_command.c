#include "../../inc/minishell.h"
#include "../../inc/utils.h"
#include "../../inc/parser.h"
#include "../../inc/colors.h"

t_ebt	*parse_command(t_minishell *ms, t_list **tokens)
{
	t_token		*token;
	t_command	*command;
	t_ebt		*ebt;
	t_redir		*redir;

	token = peek(*tokens);
	command = NULL;
	ebt = NULL;
	if (token == NULL || is_close_parenthesis(token))
	{
		ms->last_exit_status = 1;
		ft_printf(RED "\nparse error\n" RST);
		return (NULL);
	}
	if (token->type != WORD && !is_open_parenthesis(token)
		&& !is_angle_bracket(token))
	{
		ms->last_exit_status = 1;
		ft_printf(RED "\nparse error in index: %d - %s\n" RST,
			token->input_start_idx, token->value);
		return (NULL);
	}
	if (token->type == WORD || is_angle_bracket(token))
	{
		token = eat(tokens);
		command = safe_malloc(sizeof(t_command));
		command->args = NULL;
		command->command = NULL;
		command->heredoc = false;
		command->heredoc_word = NULL;
		command->redirections = NULL;
		command->command = NULL;
		if (token->type == WORD)
			command->command = ft_strdup(token->value);
		else if (token->type == O_ANGLE_BRACKET
			|| token->type == C_DANGLE_BRACKET)
		{
			ms->last_exit_status = 1;
			ft_printf(RED "Error: unexpected token '%s'\n" RST, token->value);
			free_command(command);
			return (NULL);
		}
		else if (token->type == O_DANGLE_BRACKET)
		{
			token = eat(tokens);
			command->heredoc = true;
			if (token != NULL && token->type == WORD)
				command->heredoc_word = ft_strdup(token->value);
			else
			{
				ms->last_exit_status = 1;
				ft_printf(RED "Error: expected command after '<<'\n" RST);
				free_command(command);
				return (NULL);
			}
		}
		else if (token->type == C_ANGLE_BRACKET)
		{
			redir = safe_malloc(sizeof(t_redir));
			redir->from = RT_STDOUT;
			redir->to = RT_WRITE;
			token = eat(tokens);
			if (token == NULL || token->value == NULL)
			{
				ms->last_exit_status = 1;
				ft_printf(RED "Error: expected filename after '>'\n" RST);
				free_command(command);
				free(redir);
				return (NULL);
			}
			redir->filename = ft_strdup(token->value);
			command->redirections = ft_lstnew(redir);
		}
		while (is_primary_token(peek(*tokens)))
		{
			if (is_angle_bracket(peek(*tokens)))
			{
				token = eat(tokens);
				redir = safe_malloc(sizeof(t_redir));
				redir->filename = NULL;
				redir->from = RT_STDIN;
				redir->to = RT_STDOUT;
				if (token->type == O_ANGLE_BRACKET)
				{
					redir->from = RT_STDIN;
					redir->to = RT_READ;
					token = eat(tokens);
					if (token == NULL || token->value == NULL)
					{
						ms->last_exit_status = 1;
						ft_printf(RED "Error: expected filename after '<'\n" RST);
						free_command(command);
						free(redir);
						return (NULL);
					}
					redir->filename = ft_strdup(token->value);
				}
				else if (token->type == C_ANGLE_BRACKET)
				{
					redir->from = RT_STDOUT;
					redir->to = RT_WRITE;
					token = eat(tokens);
					if (token == NULL || token->value == NULL)
					{
						ms->last_exit_status = 1;
						ft_printf(RED "Error: expected filename after '>'\n" RST);
						free_command(command);
						free(redir);
						return (NULL);
					}
					redir->filename = ft_strdup(token->value);
				}
				else if (token->type == O_DANGLE_BRACKET)
				{
					command->heredoc = true;
					token = eat(tokens);
					if (token == NULL || token->value == NULL)
					{
						ms->last_exit_status = 1;
						ft_printf(RED "Error: expected filename after '>'\n" RST);
						free_command(command);
						free(redir);
						return (NULL);
					}
					command->heredoc_word = ft_strdup(token->value);
					free(redir);
					continue ;
				}
				else if (token->type == C_DANGLE_BRACKET)
				{
					redir->from = RT_STDOUT;
					redir->to = RT_APPEND;
					token = eat(tokens);
					if (token == NULL || token->value == NULL)
					{
						ms->last_exit_status = 1;
						ft_printf(RED "Error: expected filename after '>'\n" RST);
						free_command(command);
						free(redir);
						return (NULL);
					}
					redir->filename = ft_strdup(token->value);
				}
				if (command->redirections == NULL)
					command->redirections = ft_lstnew(redir);
				else
					ft_lstadd_back(&command->redirections, ft_lstnew(redir));
			}
			else if (peek(*tokens)->type == BSLASH)
			{
				token = eat(tokens);
				continue ;
			}
			else if (peek(*tokens)->type == CMD_SUB)
			{
				ms->last_exit_status = 1;
				ft_printf(RED "Error: command substitution not available\n" RST);
				free_command(command);
				return (NULL);
			}
			else
			{
				token = eat(tokens);
				add_string(&command->args, ft_strdup(token->value));
			}
		}
		ebt = create_ebt();
		ebt->command = command;
	}
	else if (token->type == O_CURLY || token->type == O_SQUARE
		|| token->type == O_BRACKETS)
	{
		eat(tokens);
		if (token->type == O_BRACKETS)
		{
			ebt = create_ebt();
			ebt->type = EBT_OP_SUBSHELL;
			ebt->left = parse_expr(ms, tokens);
			if (ebt->left == NULL || !tokens || !*tokens
				|| !peek(*tokens)->value)
				if (expect(ms, tokens, token->type + 1,
						"syntax error near unexpected ')'\n") == NULL)
				{
					free_ebt(ebt);
					return (NULL);
				}
			if (expect(ms, tokens, token->type + 1,
					"expected closing bracket\n") == NULL)
			{
				free_ebt(ebt);
				return (NULL);
			}
		}
		else if (token->type == O_CURLY)
		{
			ebt = create_ebt();
			ebt->type = EBT_OP_SUBSHELL;
			ebt->left = parse_expr(ms, tokens);
			if (ebt->left == NULL || !tokens || !*tokens
				|| !peek(*tokens)->value)
				if (expect(ms, tokens, token->type + 1,
						"syntax error near unexpected '}'\n") == NULL)
				{
					free_ebt(ebt);
					return (NULL);
				}
			if (expect(ms, tokens, token->type + 1,
					"expected closing curly bracket\n") == NULL)
			{
				free_ebt(ebt);
				return (NULL);
			}
		}
		else if (token->type == O_SQUARE)
		{
			ebt = create_ebt();
			ebt->type = EBT_OP_SUBSHELL;
			ebt->left = parse_expr(ms, tokens);
			if (ebt->left == NULL || !tokens || !*tokens
				|| !peek(*tokens)->value)
				if (expect(ms, tokens, token->type + 1,
						"syntax error near unexpected ']'\n") == NULL)
				{
					free_ebt(ebt);
					return (NULL);
				}
			if (expect(ms, tokens, token->type + 1,
					"expected closing square bracket\n") == NULL)
			{
				free_ebt(ebt);
				return (NULL);
			}
		}
		else
		{
			ebt = parse_expr(ms, tokens);
			if (expect(ms, tokens, C_PARENTHESES, "expected ')'\n") == NULL)
			{
				free_ebt(ebt);
				return (NULL);
			}
		}
		return (ebt);
	}
	return (ebt);
}

