/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:33:51 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/01 11:39:08 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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

#endif
