#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "minishell.h"

t_lexer		*expander(t_minishell *ms, t_lexer *lex);

void		substitute_envs(t_minishell *ms, char **value);

void		handle_around_single_quotes(char **str);
void		handle_around_double_quotes(char **str);
void		handle_quotes(char **str);

void		substitute_escape_chars(char **str);
void		handle_escape_chars(char **str);

#endif
