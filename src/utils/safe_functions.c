/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:15:29 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/13 16:20:01 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/utils.h"
#include "../../libs/ft_printf/inc/ft_printf.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
	{
		ft_printf(RED "Error with the malloc, probably your computer memory"
			"reached its limit and it is going to explode in 3, 2"
			", 1..." RST);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
