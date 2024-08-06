/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:54:41 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:54:51 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

char	*convert_redir_type_to_string(t_red_type type)
{
	if (type == RT_STDIN)
		return ("STDIN");
	if (type == RT_STDOUT)
		return ("STDOUT");
	if (type == RT_STDERR)
		return ("STDERR");
	if (type == RT_WRITE)
		return ("WRITE");
	if (type == RT_APPEND)
		return ("APPEND");
	if (type == RT_READ)
		return ("READ");
	return ("UNKNOWN");
}

char	*convert_ebt_op_to_string(t_ebt_op type)
{
	if (type == EBT_OP_OR)
		return ("OR");
	if (type == EBT_OP_AND)
		return ("AND");
	if (type == EBT_OP_PIPE)
		return ("PIPE");
	if (type == EBT_OP_COMMAND)
		return ("COMMAND");
	if (type == EBT_OP_SUBSHELL)
		return ("SUBSHELL");
	if (type == EBT_OP_SEMICOLON)
		return ("SEMICOLON");
	if (type == EBT_OP_COMMAND_SUBS)
		return ("COMMAND_SUBS");
	return ("UNKNOWN");
}

t_ebt_op	convert_type_to_ebt_op(t_token_type type)
{
	if (type == DAND)
		return (EBT_OP_AND);
	if (type == OR)
		return (EBT_OP_OR);
	if (type == PIPE)
		return (EBT_OP_PIPE);
	if (type == SEMICOLON)
		return (EBT_OP_SEMICOLON);
	return (EBT_OP_COMMAND);
}
