#include "../../inc/colors.h"
#include "../../inc/lexer.h"
#include "../../inc/utils.h"

t_token	*create_empty_token(void)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	token->input_start_idx = 0;
	token->current_idx = 0;
	token->value = NULL;
	token->type = 0;
	return (token);
}

t_token	*create_token(char *value, t_token_type type, int input_start_idx,
		int current_idx)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	token->input_start_idx = input_start_idx;
	token->current_idx = current_idx;
	token->value = value;
	token->type = type;
	return (token);
}

t_lexer	*create_lexer(void)
{
	t_lexer	*lexer;

	lexer = safe_malloc(sizeof(t_lexer));
	lexer->size = 0;
	lexer->tokens = NULL;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer, char *input)
{
	if (input[lexer->size] != '\0' && lexer->size <= (int)ft_strlen(input))
		lexer->size++;
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	lexer_skip_whitespace(t_lexer *lexer, char *input)
{
	while (input[lexer->size] && ft_isspace(input[lexer->size]))
		lexer_advance(lexer, input);
}

void	lexer_push_token(t_lexer *lex, t_token *token)
{
	if (!lex->tokens)
		lex->tokens = ft_lstnew(token);
	else
		ft_lstadd_back(&lex->tokens, ft_lstnew(token));
}

void	lexer_push_advance(t_lexer *lex, t_token *token, char *input)
{
	int	i;

	lexer_push_token(lex, token);
	i = -1;
	while (++i < token->current_idx - token->input_start_idx)
		lexer_advance(lex, input);
}

bool	is_parenthesis(char c)
{
	return (c == '(' || c == ')' || c == '{' || c == '}' || c == '['
		|| c == ']');
}

bool	lexer_create_parenthesis(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (input[lex->size] == '(')
		type = O_BRACKETS;
	else if (input[lex->size] == ')')
		type = C_BRACKETS;
	else if (input[lex->size] == '{')
		type = O_CURLY;
	else if (input[lex->size] == '}')
		type = C_CURLY;
	else if (input[lex->size] == '[')
		type = O_BRACKETS;
	else if (input[lex->size] == ']')
		type = C_BRACKETS;
	value = ft_char_to_string(input[lex->size]);
	token = create_token(value, type, lex->size, lex->size + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	is_dollar(char c)
{
	return (c == '$');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool is_single_alone_operator(char c)
{
	return (c == ';' || c == '\n' || c == '\\');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == '!'
		|| c == '+' || c == '-');
}

bool	is_single_operator(char *input, int idx)
{
	if (!input)
		return (false);
	return (is_operator(input[idx]) && (input[idx + 1] == '\0'
			|| ft_isspace(input[idx + 1])));
}

bool	is_double_operator(char *input, int idx)
{
	char	c;

	if (!input)
		return (false);
	c = input[idx];
	return ((c == '|' || c == '&' || c == '<' || c == '>') && c == input[idx
		+ 1]);
}

bool	lexer_create_operator(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (input[lex->size] == '|')
		type = PIPE;
	else if (input[lex->size] == '&')
		type = AND;
	else if (input[lex->size] == '<')
		type = O_ANGLE_BRACKET;
	else if (input[lex->size] == '>')
		type = C_ANGLE_BRACKET;
	else if (input[lex->size] == '!')
		type = MARK;
	else if (input[lex->size] == '+')
		type = OPERATORS;
	else if (input[lex->size] == '-')
		type = OPERATORS;
	value = ft_char_to_string(input[lex->size]);
	token = create_token(value, type, lex->size, lex->size + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool lexer_create_single_alone_operator(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (input[lex->size] == ';')
		type = SEMICOLON;
	else if (input[lex->size] == '\n')
		type = N_LINE;
	else if (input[lex->size] == '\\')
		type = BSLASH;
	value = ft_char_to_string(input[lex->size]);
	token = create_token(value, type, lex->size, lex->size + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_double_operator(t_lexer *lex, char *input)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (ft_strncmp(&input[lex->size], "&&", 2) == 0)
		type = DAND;
	if (ft_strncmp(&input[lex->size], "||", 2) == 0)
		type = OR;
	if (ft_strncmp(&input[lex->size], "<<", 2) == 0)
		type = O_DANGLE_BRACKET;
	if (ft_strncmp(&input[lex->size], ">>", 2) == 0)
		type = C_DANGLE_BRACKET;
	value = ft_substr(input, lex->size, 2);
	token = create_token(value, type, lex->size, lex->size + 2);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_word(t_lexer *lex, char *input)
{
	int				len;
	int				start;
	t_token_type	type;
	char			*value;
	t_token			*token;

	len = 1;
	start = lex->size;
	while (input[start + len] && ft_isprint(input[start + len])
		&& !is_operator(input[start + len]) && !is_parenthesis(input[start
			+ len]) && !ft_isspace(input[start + len]))
		len++;
	type = WORD;
	value = ft_substr(input, start, len);
	ft_printf("here: %d, %s\n", len, value);
	token = create_token(value, type, lex->size, lex->size + len);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_between_quotes(t_lexer *lex, char *input)
{
	t_token_type	type;
	char			*value;
	t_token			*token;
	int				i;
	int				start;

	i = 0;
	start = lex->size;
	if (input[start + i] == '\'')
	{
		i++;
		while (input[start + i] && input[start + i] != '\'')
			i++;
	}
	else if (input[start + i] == '"')
	{
		i++;
		while (input[start + i] && input[start + i] != '"')
			i++;
	}
	type = WORD;
	value = ft_substr(input, start, i + 1);
	token = create_token(value, type, start, start + i + 1);
	lexer_push_advance(lex, token, input);
	return (true);
}

bool	lexer_create_dollar(t_lexer *lex, char *input)
{
	t_token_type	type;
	char			*value;
	t_token			*token;

	if (ft_strncmp(&input[lex->size], "$?", 2) == 0)
	{
		type = EXIT_STATUS;
		value = ft_substr(input, lex->size, 2);
		token = create_token(value, type, lex->size, lex->size + 2);
		lexer_push_advance(lex, token, input);
		return (true);
	}
	else if (ft_strncmp(&input[lex->size], "$(", 2) == 0)
	{
		type = CMD_SUB;
		value = ft_substr(input, lex->size, 2);
		token = create_token(value, type, lex->size, lex->size + 2);
		lexer_push_advance(lex, token, input);
		return (true);
	}
	return (lexer_create_word(lex, input));
}

bool	lexer_get_tokens(t_lexer *lex, char *input)
{
	bool	success;

	success = true;
	while (input[lex->size] && success)
	{
		lexer_skip_whitespace(lex, input);
		if (input[lex->size] == '\0')
			break ;
		if (is_parenthesis(input[lex->size]))
			success = lexer_create_parenthesis(lex, input);
		else if (is_single_alone_operator(input[lex->size]))
			success = lexer_create_single_alone_operator(lex, input);
		else if (is_single_operator(input, lex->size))
			success = lexer_create_operator(lex, input);
		else if (is_double_operator(input, lex->size))
			success = lexer_create_double_operator(lex, input);
		else if (is_dollar(input[lex->size]))
			success = lexer_create_dollar(lex, input);
		else if (is_quote(input[lex->size]))
			success = lexer_create_between_quotes(lex, input);
		else
			success = lexer_create_word(lex, input);
	}
	return (success);
}

void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free(token->value);
	free(token);
}

void	free_lexer(t_lexer *lex)
{
	ft_lstclear(&lex->tokens, free_token);
	free(lex);
}

t_lexer	*lexer(char *input)
{
	t_lexer	*lex;

	lex = create_lexer();
	if (lexer_get_tokens(lex, input))
		return (lex);
	ft_printf(RED "Lexer error\n" RST);
	return (NULL);
}
