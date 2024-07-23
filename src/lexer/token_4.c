#include "../../inc/lexer.h"

int	count_between_quotes(char *trim_input, t_token_type *type, int *count)
{
	int	i;

	i = 0;
	if (trim_input[i] == '\'')
	{
		i++;
		while (trim_input[i] != '\'' && trim_input[i])
			i++;
	}
	else if (trim_input[i] == '\"')
	{
		i++;
		while (trim_input[i] != '\"' && trim_input[i])
			i++;
	}
	*type = WORD;
	*count = i;
	return (i);
}
