/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ebt_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:55:29 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 18:23:23 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"

t_redir *create_redir(void)
{
	t_redir	*redir;

	redir = safe_malloc(sizeof(t_redir));
	redir->filename = NULL;
	redir->from = RT_STDIN;
	redir->to = RT_STDOUT;
	return (redir);
}

t_command	*create_command(void)
{
	t_command	*command;

	command = safe_malloc(sizeof(t_command));
	command->args = NULL;
	command->command = NULL;
	command->heredoc = false;
	command->heredoc_word = NULL;
	command->redirections = NULL;
	command->command = NULL;
	return (command);
}

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
