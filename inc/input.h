#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

char	*get_input(t_minishell *ms);
bool	handle_input(t_minishell *ms, char *input);

#endif
