#include "../../inc/glob.h"

bool	match_pattern(const char *pattern, const char *filename)
{
	if (*pattern == '\0')
		return (*filename == '\0');
	if (*pattern == '*')
		return (match_pattern(pattern + 1, filename) || (*filename
				&& match_pattern(pattern, filename + 1)));
	if (*pattern == *filename)
		return (match_pattern(pattern + 1, filename + 1));
	return (false);
}

char	**expand_wildcard(char **args)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**expanded_args;
	int				expanded_count;
	int				i;
	char			**new_expanded_args;
	char			**final_expanded_args;

	expanded_args = NULL;
	expanded_count = 0;
	i = 0;
	while (args && args[i])
	{
		if (ft_strchr(args[i], '*') != NULL)
		{
			dir = opendir(".");
			if (!dir)
			{
				ft_putstr_fd("Error: opendir failed\n", STDERR_FILENO);
				i++;
				continue ;
			}
			entry = readdir(dir);
			while (entry != NULL)
			{
				if (match_pattern(args[i], entry->d_name))
				{
					new_expanded_args = malloc(sizeof(char *) * (expanded_count
								+ 1));
					if (expanded_args)
					{
						memcpy(new_expanded_args, expanded_args, sizeof(char *)
							* expanded_count);
						free(expanded_args);
					}
					new_expanded_args[expanded_count] = ft_strdup(entry->d_name);
					expanded_args = new_expanded_args;
					expanded_count++;
				}
				entry = readdir(dir);
			}
			closedir(dir);
		}
		else
		{
			new_expanded_args = malloc(sizeof(char *) * (expanded_count + 1));
			if (expanded_args)
			{
				memcpy(new_expanded_args, expanded_args, sizeof(char *)
					* expanded_count);
				free(expanded_args);
			}
			new_expanded_args[expanded_count] = ft_strdup(args[i]);
			expanded_args = new_expanded_args;
			expanded_count++;
		}
		i++;
	}
	if (expanded_args)
	{
		final_expanded_args = malloc(sizeof(char *) * (expanded_count + 1));
		memcpy(final_expanded_args, expanded_args, sizeof(char *)
			* expanded_count);
		final_expanded_args[expanded_count] = NULL;
		free(expanded_args);
		expanded_args = final_expanded_args;
	}
	ft_free_2d_array((void **)args);
	return (expanded_args);
}
