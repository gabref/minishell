#ifndef GLOB_H
# define GLOB_H

# include "minishell.h"
#include "utils.h"
# include <dirent.h>
# include <stdbool.h>
# include <stdlib.h>

char	**expand_wildcard(char **args);

#endif
