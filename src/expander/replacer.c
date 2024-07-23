#include "../../inc/expander.h"

/*_____________________________HANDLE_DOLLAR_CASE_______________________________
Description:
		This function handles the case of the environment variables. It extracts
the name of the environment variable and gets its value. It then joins the value
		to the new argument.

Return:
		0 if the function is successful
		-1 if the function fails

1. Increment start to skip the $ character
2. Extract the name of the environment variable and the bracket if it is present
3. Get the value of the environment variable
4. Join the env value to the new_argument
5. Increment start to skip the environment variable name and the bracket
*/
int	handle_dollar_case(t_minishell *ms, char **start, char **end, char **narg)
{
	int		bracket;
	char	*env_variable_name;
	char	*env_variable_value;

	// env_variable_name = NULL;
	// env_variable_value = NULL;
	(*start)++;                                                          // 1
	env_variable_name = extract_env_variable_name(start, end, &bracket); // 2
	if (env_variable_name == NULL)
		return (-1); // se ritorna -1 qui non ho allocato nulla
	/*get_env_var_name dealloca la stringa allocata da extract_env_var_name*/
	env_variable_value = get_env_variable_value(ms, env_variable_name); // 3
	/*se riesce ha allocato, se non riesce ho deallocato*/
	*narg = join_new_arg(*narg, env_variable_value); // 4
	if (*narg == NULL)
		return (-1);
	*start = *end + bracket; // 5
	return (0);
}

/*_______________________HANDLE_PLAIN_TEXT_CASE_________________________________
Description:
		This function handles the case of plain text. It extracts the plain text
and joins it to the new argument.

Return:
		0 if the function is successful
		-1 if the function fails


1. Extract the plain text

2. Join the plain text to the new argument
*/
int	handle_plain_text_case(char **start, char **end, char **new_arg)
{
	char	*plain_text;

	// plain_text = NULL;
	/*extract_plain_text alloca se riesce,
			non ho allocato nulla se restituisce NULL*/
	plain_text = extract_plain_text(start, end); // 1
	if (plain_text == NULL)
	{
		return (-1);
	}
	/*se riesce ha allocato, se non riesce ho deallocato*/
	*new_arg = join_new_arg(*new_arg, plain_text); // 2
	free(plain_text);
	if (*new_arg == NULL)
		return (-1);
	return (0);
}

/*************************************DA
 * QUI*************************************/
/*VEDERE SE VA BENE COSI*/
// int handle_wildcards_case(t_minishell *ms, char **start/*, char **end*/,
// char **new_arg)
//{
/*char *wildcards;
char	*wildcards_value;

(*start)++;
wildcards = extract_wildcards(start, end);
if (wildcards == NULL)
	return (-1);  //se ritorna -1 qui non ho allocato nulla

wildcards_value = get_wildcards_value(ms, wildcards);


se riesce ha allocato, se non riesce ho deallocato
*new_arg = join_new_arg(*new_arg, wildcards_value);
if (*new_arg == NULL)
	return (-1);

*start = *end;

return (0);*/
//}
/*******************************************************************************/
int	process_text(t_minishell *ms, char **start, char **end, char **new_arg)
{
	int	result;

	result = 0;
	if (ft_strchr(*start, '*') != NULL)
		result = parse_wildcards(start, new_arg);
	else if (**start == '$')
		result = handle_dollar_case(ms, start, end, new_arg);
	// else if (**start == '*')
	//    result = handle_wildcards_case(ms, start, /*end,*/ new_arg);
	else
		result = handle_plain_text_case(start, end, new_arg);
	printf("result: %i\n", result);
	return (result);
}

/*_______________________________ARG_REPLACE____________________________________
Description:
		This function replaces the environment variables in the argument
with their values. It also handles the case of plain text. It can hendle
the following cases: $HOME $HOME/qualcosa $USER_name
		$PATH:additional_path
		dir/$USER
		path/to/$VARIABLE
		prefix_$VARIABLE
		qualcosa/$QUALCOSA/qualcosa
		${USER}_name
		${VAR1}${VAR2}
		$USER${VARIABLE}_suffix
		prefix${HOME}/path

Return:
		0 if the function is successful
		-1 if the function fails


1. Start points to the beginning of the argument
2. new_arg is the new argument that will be returned
3. Cicling through the argument, if we find a $ we call
handle_dollar_case, otherwise we call handle_plain_text_case

		example 1: $HOME -> handle_dollar_case
		example 2: something/$HOME
		-> keep calling handle_plain_text_case until we find a $
																->
handle_dollar_case
4. free the old argument and assign the new one to the argument
*/
int	arg_replace(t_minishell *ms, char **arg)

{
	char *new_arg;
	char *start;

	char *end;
	int result;

	start = *arg;            // 1
	new_arg = ft_strdup(""); // 2
	if (new_arg == NULL)
		return (-1);
	if (*start) // 3
	{
		result = process_text(ms, &start, &end, &new_arg);
		printf("start: %s\n", start);
		printf("new_arg: %s\n", new_arg);
		printf("%i\n", result);
		if (result == -1)

		{
			free(new_arg);
			return (-1);
		}
	}
	if (new_arg && *new_arg) // 4
	{
		free(*arg);
		*arg = new_arg;
	}

	return (0);
}
