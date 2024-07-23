#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/*da cancellare*************************/
void	create_ebt_test(t_ebt **ebt);
void	printtree(t_ebt *root);
void	free_tree(t_ebt *root);
/*****************************************/

/*expander*/
int		expander(t_minishell *ms);

/*replacer_utils*/
char	*join_new_arg(char *new_arg, char *value);
char	*extract_env_variable_name(char **start, char **end, int *bracket);
char	*extract_plain_text(char **start, char **end);
char	*get_env_variable_value(t_minishell *ms, char *env_variable_name);

/*replacer*/
int		handle_dollar_case(t_minishell *ms, char **start, char **end,
			char **new_arg);
int		handle_plain_text_case(char **start, char **end, char **new_arg);
int		arg_replace(t_minishell *ms, char **arg);

/*wildcards*/
int		match_pattern(const char *pattern, const char *str);
int		parse_wildcards(char **input, char **new_arg);

#endif
