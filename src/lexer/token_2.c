#include "../../inc/lexer.h"

int	is_punctuation(char *trim_input, t_token_type *type)
{
	if (trim_input[0] == '.')
	{
		*type = DOT;
		return (1);
	}
	else if (trim_input[0] == ';')
	{
		*type = SEMICOLON;
		return (1);
	}
	else if (trim_input[0] == ':')
	{
		*type = COLON;
		return (1);
	}
	else if (trim_input[0] == ',')
	{
		*type = COMMA;
		return (1);
	}
	else
		return (0);
}

int	is_nline_bslash_tilde(char *trim_input, t_token_type *type)
{
	if (trim_input[0] == '\n')
	{
		*type = N_LINE;
		return (1);
	}
	else if (trim_input[0] == 92)
	{
		*type = BSLASH;
		return (1);
	}
	else if (trim_input[0] == 126)
	{
		*type = TILDE;
		return (1);
	}
	else
		return (0);
}

int	is_operator(char *trim_input, t_token_type *type, int *count)
{
	int	i;

	*count = 1;
	if ((trim_input[0] == '-' && (trim_input[1] == ' '
				|| trim_input[1] == '\t')) || trim_input[0] == '+')
	{
		*type = OPERATORS;
		return (*count);
	}
	else if (trim_input[0] == '-' && ft_isprint_lex(trim_input[1]))
	{
		i = 1;
		while (trim_input[i] != ' ' && trim_input[i] != '\t'
			&& trim_input[i] != ')' && trim_input[i] != ']'
			&& trim_input[i] != '}' && trim_input[i])
			i++;
		*type = WORD;
		*count = (i - 1);
		return (*count);
	}
	else
		return (0);
}

int	is_logical_or_pipe(char *trim_input, t_token_type *type)
{
	if (trim_input[0] == '&' && trim_input[1] == '&')
	{
		*type = DAND;
		return (2);
	}
	else if (trim_input[0] == '&')
	{
		*type = AND;
		return (1);
	}
	else if (trim_input[0] == '|' && trim_input[1] == '|')
	{
		*type = OR;
		return (2);
	}
	else if (trim_input[0] == '|')
	{
		*type = PIPE;
		return (1);
	}
	else
		return (0);
}

int	is_redir_or_her(char *trim_input, t_token_type *type)

{
	if (trim_input[0] == '>' && trim_input[1] == '>')
	{
		*type = OUT_APPEND;
		return (2);
	}
	else if (trim_input[0] == '>')
	{
		*type = OUT_APPEND;
		return (1);
	}
	else if (trim_input[0] == '<' && trim_input[1] == '<')
	{
		*type = HEREDOC;
		return (2);
	}
	else if (trim_input[0] == '<')

	{
		*type = IN;
		return (1);
	}
	else
		return (0);
}
