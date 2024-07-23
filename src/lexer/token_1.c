#include "../../inc/lexer.h"

static int	o_parentheses(char *str, t_token_type *type)
{
	if (str[0] == '(')
	{
		*type = O_BRACKETS;
		return (1);
	}
	else if (str[0] == '{')
	{
		*type = O_CURLY;
		return (1);
	}
	else if (str[0] == '[')
	{
		*type = O_SQUARE;
		return (1);
	}
	else
	return (0);
}

static int	c_parentheses(char *str, t_token_type *type)
{
	if (str[0] == ')')
	{
		*type = C_BRACKETS;
		return (1);
	}
	else if (str[0] == '}')
	{
		*type = C_CURLY;
		return (1);
	}
	else if (str[0] == ']')
	{
		*type = C_SQUARE;
		return (1);
	}
	else
		return (0);
}

int	is_parentheses(char *trim_input, t_token_type *type)
{
	if (o_parentheses(trim_input, type) || c_parentheses(trim_input, type))
		return (1);
	else
		return (0);
}

int	is_mark(char *trim_input, t_token_type *type)
{
	if (trim_input[0] == '?' || trim_input[0] == '!')
	{
		*type = MARK;
		return (1);
	}
	else
		return (0);
}

int	is_quote(char *trim_input, t_token_type *type)
{
	if (trim_input[0] == 34)
	{
		*type = DOUBLE_Q;
		return (1);
	}
	else if (trim_input[0] == 39)
	{
		*type = SINGLE_Q;
		return (1);
	}
	else
		return (0);
}
