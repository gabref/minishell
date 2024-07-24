#include "../../inc/lexer.h"

int	is_exti_or_cmd_sub(char *trim_input, t_token_type *type)

{
	if (trim_input[0] == '$' && trim_input[1] == '?')
	{
		*type = EXIT_STATUS;

		return (1);
	}
	else if (trim_input[0] == '$' && (trim_input[1] == '('
			|| trim_input[1] == '[' || trim_input[1] == '{'))
	{
		*type = CMD_SUB;
		return (1);
	}
	else
		return (0);
}

/*Restituisce 1 se trova un dollaro separato da spazi, il numero di caratteri se
  concatenato ad essi, 0 altrimenti*/
int	is_dollar(char *trim_input, t_token_type *type, int *count)
{
	int	i;

	*count = 1;
	if (trim_input[0] == '$' && (trim_input[1] == ' ' || trim_input[1] == '\t'))
	{
		*type = WORD;
		return (*count);
	}
	else if (trim_input[0] == '$' && ft_isprint_lex(trim_input[1]))
	{
		i = 1;
		while (trim_input[i] != ' ' && trim_input[i] != '\t' && trim_input[i])
			i++;
		*type = DOLLAR;
		*count = (i - 1); // per lo spazio
		return (*count);
	}
	else
		return (0);
}

int	is_istruction(char *trim_input, t_token_type *type)

{
	if (ft_strncmp_lex(trim_input, "set", 3) == 0)

	{
		*type = INSTRUCTION;
		return (1);
	}
	else if (ft_strncmp_lex(trim_input, "unset", 5) == 1)
	{
		*type = INSTRUCTION;

		return (2);
	}

	return (0);
}

/*
Considererà come glob:
-> *       singolo
-> *..     seguito da caratteri qualsiasi da 33 a 126
*/
int	is_globe(char *trim_input, t_token_type *type, int *count)
{
	int	i;

	*count = 1;
	if (trim_input[0] == '*' && (trim_input[1] == ' ' || trim_input[1] == '\t'))
	{
		*type = GLOB;
		return (*count);
	}
	else if (trim_input[0] == '*' && ft_isprint_lex(trim_input[1]))
	{
		i = 1;
		while (trim_input[i] != ' ' && trim_input[i] != '\t' && trim_input[i])
			i++;
		*type = GLOB;
		*count = (i - 1); // per lo spazio
		return (*count);
	}
	else
		return (0);
}

/*
CASI COME QUESTI (parole con questi caratteri all'interno) SARANNO CONSIDERATE
PAROLE
..!..
...[]: Corrisponde a un singolo carattere tra quelli specificati all'interno
delle parentesi quadre.
...[!] o [^]: Corrisponde a un singolo carattere che non è tra quelli
specificati all'interno delle parentesi quadre.
...{}: Permette di specificare più stringhe alternative separate da virgole.
?  : Credo anche questa non vada considerata

Es: file[!a-b] -> parola

-> stringa di caratteri separata da spazi = WORD
-> se nella stringa ho un * = GLOB
*/
int	is_word_or_glob(char *trim_input, t_token_type *type, int *count)
{
	int		i;
	char	*tmp;

	*count = 0;
	i = 1;
	if (is_quote(trim_input, type))
		return (count_between_quotes(trim_input, type, count));
	while (trim_input[i] != ' ' && trim_input[i] != '\t' && trim_input[i] != ')'
		&& trim_input[i] != ']' && trim_input[i] != '}' && trim_input[i] != ';'
		&& trim_input[i])
		i++;
	tmp = ft_substr_lex(trim_input, 0, i);
	if ((strchr_lex(tmp, '[') && trim_input[i] == ']') || (strchr_lex(tmp, '(')
			&& trim_input[i] == ')') || (strchr_lex(tmp, '{')
			&& trim_input[i] == '}'))
		i++;
	free(tmp);
	tmp = ft_substr_lex(trim_input, 0, i);
	if (strchr_lex(tmp, '*'))
		*type = GLOB;
	else
		*type = WORD;
	*count = (i - 1);
	free(tmp);
	return (*count);
}
