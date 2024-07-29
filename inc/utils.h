/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:33:51 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/24 16:47:52 by galves-f         ###   ########.fr       */
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
int		get_global_error(void);
void	set_global_error(int error_code);

#endif