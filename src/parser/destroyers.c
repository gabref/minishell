/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:54:57 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 14:54:58 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

void	free_redirection(void *ptr)
{
	t_redir	*redir;

	redir = (t_redir *)ptr;
	if (redir->filename)
		free(redir->filename);
	free(redir);
}

void	free_command(t_command *command)
{
	if (command->command)
		free(command->command);
	if (command->heredoc_word)
		free(command->heredoc_word);
	if (command->redirections)
		ft_lstclear(&command->redirections, &free_redirection);
	ft_free_2d_array((void **)command->args);
	free(command);
}

void	free_ebt(t_ebt *ebt)
{
	if (ebt == NULL)
		return ;
	if (ebt->command)
		free_command(ebt->command);
	if (ebt->left)
		free_ebt(ebt->left);
	if (ebt->right)
		free_ebt(ebt->right);
	free(ebt);
}
