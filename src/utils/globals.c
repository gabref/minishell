/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:01:39 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:01:49 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

static int	g_signal;

void	set_global_signal(int signum)
{
	g_signal = signum;
}

int	get_global_signal(void)
{
	return (g_signal);
}
