#include "../../inc/utils.h"

static int g_signal;

void set_global_signal(int signum)
{
	g_signal = signum;
}

int get_global_signal(void)
{
	return (g_signal);
}

void add_string_front(char ***array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (*array)
		while ((*array)[i])
			i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	i = 0;
	new_array[0] = str;
	if (*array)
	{
		while ((*array)[i])
		{
			new_array[i + 1] = (*array)[i];
			i++;
		}
		free(*array);
	}
	new_array[i + 1] = NULL;
	*array = new_array;
}

