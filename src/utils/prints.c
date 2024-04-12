/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:56:14 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/12 11:52:47 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/colors.h"
#include "../../libs/ft_printf/inc/ft_printf.h"

void	print_welcome(void)
{
	ft_printf(TB00 TB01);
	ft_printf(RNT0 RNT1);
	ft_printf(RNT0 RNT1);
	ft_printf(PBT0 LIGHT_CYAN TT00 PAT0);
	ft_printf(PBT0 LIGHT_CYAN TT01 PAT0);
	ft_printf(PBT0 LIGHT_CYAN TT02 PAT0);
	ft_printf(RNT0 RNT1);
	ft_printf(RNT0 RNT1);
	ft_printf(PBN0 LIGHT_GREEN PN01 PN02 PAN0);
	ft_printf(PBN0 LIGHT_GREEN PN03 PN04 PAN0);
	ft_printf(PBN0 LIGHT_GREEN PN05 PN06 PAN0);
	ft_printf(PBN0 LIGHT_GREEN PN07 PN08 PAN0);
	ft_printf(PBN0 LIGHT_GREEN PN09 PN10 PAN0);
	ft_printf(PBN0 LIGHT_GREEN PN11 PN12 PAN0);
	ft_printf(PBN0 LIGHT_GREEN PN13 PN14 PAN0);
	ft_printf(PBN0 LIGHT_GREEN PN15 PN16 PAN0);
	ft_printf(RNT0 RNT1);
	ft_printf(RNT0 RNT1);
	ft_printf(BB00 BB01);
}
