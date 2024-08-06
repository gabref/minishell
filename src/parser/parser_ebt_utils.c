/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ebt_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:55:29 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:55:38 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"

t_ebt	*create_ebt(void)
{
	t_ebt	*ebt;

	ebt = safe_malloc(sizeof(t_ebt));
	ebt->type = EBT_OP_COMMAND;
	ebt->command = NULL;
	ebt->left = NULL;
	ebt->right = NULL;
	return (ebt);
}
