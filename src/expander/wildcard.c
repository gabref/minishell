/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:21:26 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/05/25 15:33:35 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

/*	verifico la presenza di "*" nella stringa input e la successiva
	corrispondenza tra la stringa input e il nome dell'elemento nella directory:

	1) primo if: se entrambe le stringhe sono vuote vi è un match e returno 1
	2) secondo if: se nella stringa input trovo "*" entro in un while che scorre l'altra stringa (nome dell'elemento nella directory) e se trovo un match chiamo la funzione ricorsivamente con pattern
		+ 1 e str
	3) terzo if: se il carattere corrente di pattern (input) è uguale a quello di str (elemento nella dir) chiamo la funzione ricorsivamente con pattern
		+ 1 e str + 1.
	4) se nessuna delle condizioni precedenti è verificata returno 0


	1 -> mathc
	0 -> no match
*/
/*******************************************************************************/
int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*str != '\0')
		{
			if (match_pattern(pattern + 1, str))
				return (1);
			str++;
		}
		return (match_pattern(pattern + 1, str));
	}
	if (*pattern == *str)
	{
		return (match_pattern(pattern + 1, str + 1));
	}
	return (0);
}

/*	funzione per gestire le wildcard
	apre la current working directory e cerca i file che matchano con la wildcard
	se vi è un match stampa il nome del file e returna 1

	1 -> match
	0 -> no match
	-1 -> errore
*/

void	join_wildcards(char **new_arg, char *entries)
{
	*new_arg = join_new_arg(*new_arg, entries);
	free(entries);
	*new_arg = join_new_arg(*new_arg, " ");
}

int	parse_wildcards(char **input, char **new_arg)
{
	char	current_directory[PATH_MAX];
		DIR *dir;
		struct dirent *entry;
		char *entries;

	if (getcwd(current_directory, sizeof(current_directory)))
	{
		dir = opendir(current_directory);
		if (dir)
		{
			while ((entry = readdir(dir)))
			{
				if (match_pattern(*input, entry->d_name))
				{
					entries = ft_strdup(entry->d_name);
					join_wildcards(new_arg, entries);
				}
			}
			closedir(dir);
			return (0);
		}
		return (-1);
	}
	return (-1);
}

/*******************************************************************************/
