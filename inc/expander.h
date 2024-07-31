#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "minishell.h"

t_lexer	*expander(t_minishell *ms, t_lexer *lex);
void	print_token(t_token *token);

#endif
