/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:33:51 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 13:57:47 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

# define MSG_ERR_ARGS "Error\nThis program doesn\'t accept arguments!!\n"

void	print_welcome(void);
void	*safe_malloc(size_t bytes);
int		get_global_signal(void);
void	set_global_signal(int signum);
void	add_string_front(char ***array, char *str);
void	substitute_str(char **str, int start, int end, char *sub);
int		find_string_2d_array(char *str, char **arr);
bool	string_all_spaces(char *str);
bool	free_and_return_bool(void *ptr, bool ret);

#endif
