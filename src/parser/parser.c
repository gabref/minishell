/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:25:57 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/23 11:28:46 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"

t_ebt		*parse_binary_expr_semicolon(t_token **tokens);
t_ebt		*parse_expr(t_token **tokens);
void		print_token(t_token *token);
t_ebt_op	convert_type_to_ebt_op(t_token_type type);

int	not_eof(t_token *token)
{
	return (token != NULL && token->type != END_OF_FILE);
}

t_token	*peek(t_token *tokens)
{
	return (tokens);
}

t_token	*eat(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	if (token == NULL)
		return (NULL);
	*tokens = (*tokens)->next;
	return (token);
}

void	expect(t_token **tokens, t_token_type type, char *err_message)
{
	t_token	*token;

	token = eat(tokens);
	if (token->type != type)
	{
		ft_printf(RED "Error: %s\n", err_message);
		ft_printf("got: %s\n" RST, token->value);
		// TODO: not exit but gracefully return error
		exit(1);
	}
}

t_ebt	*create_ebt(void)
{
	t_ebt	*ebt;

	ebt = safe_malloc(sizeof(t_ebt));
	ebt->type = EBT_OP_COMMAND;
	ebt->command = NULL;
	ebt->left = NULL;
	ebt->right = NULL;
	return (ebt);
}

char	*convert_ebt_op_to_string(t_ebt_op type)
{
	if (type == EBT_OP_OR)
		return ("OR");
	if (type == EBT_OP_AND)
		return ("AND");
	if (type == EBT_OP_PIPE)
		return ("PIPE");
	if (type == EBT_OP_COMMAND)
		return ("COMMAND");
	if (type == EBT_OP_SUBSHELL)
		return ("SUBSHELL");
	if (type == EBT_OP_SEMICOLON)
		return ("SEMICOLON");
	if (type == EBT_OP_COMMAND_SUBS)
		return ("COMMAND_SUBS");
	return ("UNKNOWN");
}

void	print_token(t_token *token)
{
	if (token == NULL)
	{
		ft_printf("NULL\n");
		return ;
	}
	ft_printf("type: %s, value: %s\n",
		convert_ebt_op_to_string(convert_type_to_ebt_op(token->type)),
		token->value);
}

void	print_command(t_command *command, int level)
{
	int	i;
	int	il;

	il = 0;
	while (il++ < level)
		ft_printf(SPACES);
	if (command == NULL)
	{
		ft_printf(GREEN_BOLD "COMMAND NULL\n" RST);
		return ;
	}
	ft_printf(GREEN_BOLD "COMMAND: %s\n" RST, command->command);
	il = 0;
	while (il++ < level)
		ft_printf(SPACES);
	if (command->heredoc_file_name)
		ft_printf("\theredoc file name: %s\n", command->heredoc_file_name);
	else
		ft_printf("\theredoc file name: NULL\n");
	il = 0;
	while (il++ < level)
		ft_printf(SPACES);
	ft_printf("\targs: [");
	i = 0;
	while (command->args && command->args[i])
	{
		ft_printf("\"%s\"", command->args[i++]);
		if (command->args[i])
			ft_printf(", ");
	}
	ft_printf("]\n");
}

void	print_ebt(t_ebt *ebt, int level)
{
	int	i;

	if (ebt == NULL)
	{
		ft_printf("NULL\n");
		return ;
	}
	ft_printf("\n");
	i = 0;
	while (i++ < level)
		ft_printf(SPACES);
	ft_printf(CYAN_BOLD "EBT_OP: %s\n" RST,
		convert_ebt_op_to_string(ebt->type));
	if (ebt->command)
		print_command(ebt->command, level);
	i = 0;
	while (i++ < level)
		ft_printf(SPACES);
	ft_printf(MAGENTA_BOLD "LEFT -> " RST);
	print_ebt(ebt->left, level + 1);
	i = 0;
	while (i++ < level)
		ft_printf(SPACES);
	ft_printf(BLUE_BOLD "RIGHT -> " RST);
	print_ebt(ebt->right, level + 1);
}

int is_open_parenthesis(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == O_SQUARE || token->type == O_CURLY || token->type == O_BRACKETS);
}

int is_close_parenthesis(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == C_SQUARE || token->type == C_CURLY || token->type == C_BRACKETS);
}

int	is_primary_token(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == WORD || token->type == IN || token->type == SINGLE_Q
		|| token->type == DOUBLE_Q || token->type == OUT_APPEND
		|| token->type == INSTRUCTION);
}

int	is_binary_token_semicolon(t_token *token)
{
	if (token == NULL)
		return (0);
	return (token->type == SEMICOLON);
}

int	is_binary_token(t_token *token)
{
	if (token == NULL)
		return (0);
	print_token(token);
	return (token->type == DAND || token->type == OR || token->type == PIPE);
}

void	add_string(char ***array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (*array)
		while ((*array)[i])
			i++;
	new_array = safe_malloc(sizeof(char *) * (i + 2));
	i = 0;
	if (*array)
	{
		while ((*array)[i])
		{
			new_array[i] = (*array)[i];
			i++;
		}
		free(*array);
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	*array = new_array;
}

void	join_string(char **str, char *to_join)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (*(*str + i))
		i++;
	while (to_join[j])
		j++;
	new_str = malloc(sizeof(char) * (i + j + 1));
	i = -1;
	while (*(*str + ++i))
		new_str[i] = *(*str + i);
	free(*str);
	j = 0;
	while (to_join[j])
		new_str[i++] = to_join[j++];
	new_str[i] = '\0';
	*str = new_str;
}

t_ebt	*parse_command(t_token **tokens)
{
	t_token		*token;
	t_command	*command;
	t_ebt		*ebt;

	token = peek(*tokens);
	command = NULL;
	ebt = NULL;
	if (token == NULL || is_close_parenthesis(token))
		return (NULL);
	if (token->type != WORD && !is_open_parenthesis(token))
	{
		ft_printf(RED "\nparse error in index: %d - %s" RST,
			token->input_start_idx, token->value);
		return (NULL);
	}
	if (token->type == WORD)
	{
		ft_printf("parsing_command: %s\n", token->value);
		token = eat(tokens);
		command = safe_malloc(sizeof(t_command));
		command->args = NULL;
		command->command = NULL;
		command->heredoc_file_name = NULL;
		command->command = ft_strdup(token->value);
		while (is_primary_token(*tokens))
		{
			token = eat(tokens);
			add_string(&command->args, ft_strdup(token->value));
		}
		ebt = create_ebt();
		ebt->command = command;
		print_command(command, 0);
	}
	else if (token->type == O_CURLY || token->type == O_SQUARE
		|| token->type == O_BRACKETS)
	{
		eat(tokens);
		if (token->type == O_BRACKETS)
		{
			printf("parsing brackets\n");
			ebt = create_ebt();
			ebt->type = EBT_OP_SUBSHELL;
			ebt->left = parse_expr(tokens);
			expect(tokens, token->type + 1, "expected closing bracket");
		}
		else if (token->type == O_CURLY)
		{
			printf("parsing curly\n");
			ebt = create_ebt();
			ebt->type = EBT_OP_SUBSHELL;
			ebt->left = parse_expr(tokens);
			expect(tokens, token->type + 1, "expected closing curly bracket");
		}
		else if (token->type == O_SQUARE)
		{
			printf("parsing square\n");
			ebt = create_ebt();
			ebt->type = EBT_OP_SUBSHELL;
			ebt->left = parse_expr(tokens);
			expect(tokens, token->type + 1, "expected closing square bracket");
		}
		else
		{
			ebt = parse_expr(tokens);
			expect(tokens, C_PARENTHESES, "expected ')'");
		}
		return (ebt);
	}
	return (ebt);
}

void	free_command(t_command *command)
{
	if (command->command)
		free(command->command);
	if (command->heredoc_file_name)
		free(command->heredoc_file_name);
	ft_free_2d_array((void **)command->args);
	free(command);
}

void	free_ebt(t_ebt *ebt)
{
	if (ebt == NULL)
		return ;
	if (ebt->command)
		free_command(ebt->command);
	if (ebt->left)
		free_ebt(ebt->left);
	if (ebt->right)
		free_ebt(ebt->right);
	free(ebt);
}

t_ebt_op	convert_type_to_ebt_op(t_token_type type)
{
	if (type == AND)
		return (EBT_OP_AND);
	if (type == OR)
		return (EBT_OP_OR);
	if (type == PIPE)
		return (EBT_OP_PIPE);
	if (type == SEMICOLON)
		return (EBT_OP_SEMICOLON);
	return (EBT_OP_COMMAND);
}

t_ebt	*parse_expr(t_token **tokens)
{
	return (parse_binary_expr_semicolon(tokens));
}

t_ebt	*parse_binary_expr(t_token **tokens)
{
	t_ebt	*left;
	t_ebt	*right;
	t_ebt	*ebt;

	left = parse_command(tokens);
	if (left == NULL)
		return (NULL);
	while (is_binary_token(*tokens))
	{
		t_token *operator= eat(tokens);
		right = parse_command(tokens);
		if (right == NULL)
		{
			free_ebt(left);
			return (NULL);
		}
		ebt = create_ebt();
		ebt->type = convert_type_to_ebt_op(operator->type);
		ebt->left = left;
		ebt->right = right;
		left = ebt;
	}
	return (left);
}

t_ebt	*parse_binary_expr_semicolon(t_token **tokens)
{
	t_ebt	*left;
	t_ebt	*right;
	t_ebt	*ebt;

	left = parse_binary_expr(tokens);
	if (left == NULL)
		return (NULL);
	while (is_binary_token_semicolon(*tokens))
	{
		t_token *operator= eat(tokens);
		right = parse_binary_expr(tokens);
		if (right == NULL)
			return (left);
		ebt = create_ebt();
		ebt->type = convert_type_to_ebt_op(operator->type);
		ebt->left = left;
		ebt->right = right;
		left = ebt;
	}
	return (left);
}

void	parse(t_minishell *ms, t_lexer *lexer)
{
	t_token	*tokens;
	t_ebt	*ebt;

	(void)ms;
	tokens = lexer->tokens;
	ebt = NULL;
	while (not_eof(tokens))
	{
		ebt = parse_expr(&tokens);
		if (ebt == NULL)
			break ;
	}
	print_ebt(ebt, 0);
	free_ebt(ebt);
}
