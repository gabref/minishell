#include "../../inc/lexer.h"

static int	token_util_one(char *trim_input, t_token_type *type)
{
	if (is_parentheses(trim_input, type))
		return (1);
	else if (is_mark(trim_input, type))
		return (1);
	else if (is_punctuation(trim_input, type))
		return (1);
	// else if (is_quote(trim_input, type))
	// 	return (1);
	else if (is_nline_bslash_tilde(trim_input, type))
		return (1);
	else
		return (0);
}

static int	token_util_two(char *trim_input, t_token_type *type)
{
	if (is_logical_or_pipe(trim_input, type) == 1)
		return (1);
	else if (is_logical_or_pipe(trim_input, type) == 2)
		return (2);
	else if (is_redir_or_her(trim_input, type) == 1)
		return (1);
	else if (is_redir_or_her(trim_input, type) == 2)
		return (2);
	else if (is_exti_or_cmd_sub(trim_input, type))
		return (2);
	else
		return (0);
}

static int	token_util_three(char *trim_input, t_token_type *type, int *count)
{
	if (is_operator(trim_input, type, count) == 1)
		return (1);
	else if (is_operator(trim_input, type, count) > 1)
		return (*count);
	else if (is_dollar(trim_input, type, count) == 1)
		return (1);
	else if (is_dollar(trim_input, type, count) > 1)
		return (*count);
	else
		return (0);
}

/*TOKEN_FINDER__________________________________________________________________
COSA FA: Trova l'indice di fine di un token nella stringa di input aggiornata
			all'ultima posizione controllata
RETURN:  Un intero corrispondente al:

				((numero di caratteri che compondono il token) - 1)

*/
int	token_finder(char *trim_input, t_token_type *type)
{
	int	count;

	if (token_util_one(trim_input, type))
		return (0);
	else if (token_util_two(trim_input, type) == 1)
		return (0);
	else if (token_util_two(trim_input, type) == 2)
		return (1);
	else if (token_util_three(trim_input, type, &count) == 1 && *type != WORD)
		return (0);
	else if (token_util_three(trim_input, type, &count) >= 1)
		return (count);
	else if (is_istruction(trim_input, type) == 1)
		return (2);
	else if (is_istruction(trim_input, type) == 2)
		return (4);
	else if (is_globe(trim_input, type, &count) == 1)
		return (0);
	else if (is_globe(trim_input, type, &count) > 1)
		return (count);
	else
		is_word_or_glob(trim_input, type, &count);
	return (count);
}

int	tokenizer(t_lexer *lex_struct, char *input)
{
	char			*token;
	int				i;
	int				start;
	t_token_type	type;

	i = -1;
	while (input[++i])
	{
		type = END_OF_FILE;
		if (input[i] == ' ' || input[i] == '\t')
			continue ;
		start = i;
		i += token_finder(input + start, &type);
		token = ft_substr_lex(input + start, 0, (i - start) + 1);
		if (token == NULL)
		{
			free_and_quit(lex_struct, token);
			return (0);
		} /* -Dealloco token se token != NULL
			-Deallocare la lista lex_struct->tokens con
			la funzione di deallocazione se != NULL
			-dealloco il puntatore a struct  lex_struct
			- ritorno NULL*/
		if (add_end(&(lex_struct->tokens), token, start, i, type))
		{
			free_and_quit(lex_struct, token);
			return (0);
		} /* -Dealloco token se token != NULL
			-Deallocare la lista lex_struct->tokens con
			la funzione di deallocazione se != NULL
			-dealloco il puntatore a struct  lex_struct
			- ritorno NULL*/
	}
	return (i);
}
