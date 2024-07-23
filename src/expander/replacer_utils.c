#include "../../inc/expander.h"

/*_____________________________JOIN_NEW_ARG_____________________________________
Description:
	This function joins the new argument with the value extracted from the

	environment variable.
*/
char	*join_new_arg(char *new_arg, char *value)
{
	char	*temp_arg;

	temp_arg = ft_strjoin(new_arg, value);
	if (!temp_arg)
	{
		if (new_arg)
			free(new_arg); /////????
		return (NULL);
	}
	free(new_arg);
	return (temp_arg);
}

/*_________________________EXTRACT_ENV_VARIABLE_NAME____________________________
Description:
	This function extracts the name of the environment variable. It extracts the
	name until it finds a non-alphanumeric character.
	NOTE: The function also handles the case of the bracket. If the variable is
			enclosed in brackets, it sets the bracket variable to 1.

Return:
	env_variable_name is the name of the environment variable

1. If the character is { or (, set the bracket variable to 1 and increment the
   start pointer

2. end points to the beginning of the argument
3. Increment end until we find a non-alphanumeric character
4. Allocate memory for the environment variable name
5. Copy the environment variable name into the allocated memory
6. Increment the start pointer to skip the environment variable name and the
   bracket
*/
char	*extract_env_variable_name(char **start, char **end, int *bracket)
{
	char	*env_variable_name;
	int		i;

	i = 0;
	*bracket = 0;
	if (**start == '{' || **start == '(') // 1
	{
		*bracket = 1;
		(*start)++;
	}
	*end = *start;                // 2
	while (ft_isalnum((*end)[i])) // 3
		i++;
	env_variable_name = malloc(i + 1); // 4
	if (env_variable_name == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(env_variable_name, *end, i + 1); // 5
	*start = *end + i + *bracket;
	*end = *start; // 6
	return (env_variable_name);
}

/*___________________________EXTRACT_PLAIN_TEXT_________________________________
Description:
	This function extracts the plain text from the argument. It extracts the text
	until it finds a $ character.

Return:
	plain_text is the extracted text


1. end points to the beginning of the argument
2. Increment end until we find a $ character
3. Extract the plain text with ft_substr
4. start points to the end of the argument
*/
char	*extract_plain_text(char **start, char **end)
{
	char	*plain_text;

	*end = *start;                // 1
	while (**end && **end != '$') // 2
		(*end)++;
	plain_text = ft_substr(*start, 0, *end - *start); // 3
	*start = *end;                                    // 4
	return (plain_text);
}

/*_________________________GET_ENC_VARIABLE_VALUE_______________________________

Description:
	This function gets the value of the environment variable. If the variable is
	not found, it returns an empty string.


1. Get the value of the environment variable with ms_get_env
2. Free the name of the environment variable
3. If the value is NULL, assign an empty string to it
*/
char	*get_env_variable_value(t_minishell *ms, char *env_variable_name)
{
	char	*env_variable_value;

	env_variable_value = ms_get_env(ms, env_variable_name); // 1
	free(env_variable_name);                                // 2
	if (env_variable_value == NULL)                         // 3
		env_variable_value = ft_strdup("");
	return (env_variable_value);
}
