/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:48:02 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/24 16:48:04 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

static int g_global_error= 0;

void				set_global_error(int error_code)
{
	g_global_error = error_code;
}

int get_global_error()
{
	return (g_global_error);
}
