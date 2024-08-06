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

int	find_string_2d_array(char *str, char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (-1);
	while (arr && arr[i])
	{
		if (ft_strncmp(str, arr[i], ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	substitute_str(char **str, int start, int end, char *sub)
{
	char	*newstr;
	int		str_len;
	int		sub_len;
	int		i;
	int		newstr_len;
	int		j;

	str_len = ft_strlen(*str);
	sub_len = ft_strlen(sub);
	newstr_len = str_len - (end - start) + sub_len;
	newstr = safe_malloc(sizeof(char) * newstr_len + 1);
	i = -1;
	while (++i < start)
		newstr[i] = (*str)[i];
	j = 0;
	while (i < start + sub_len)
		newstr[i++] = sub[j++];
	while (i < newstr_len)
		newstr[i++] = (*str)[end++];
	newstr[i] = '\0';
	free(*str);
	*str = newstr;
}

bool	string_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
			return (false);
		i++;
	}
	return (true);
}

bool free_and_return_bool(void *ptr, bool ret)
{
	free(ptr);
	return (ret);
}
