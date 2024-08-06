/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:55:52 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 15:07:34 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/minishell.h"
#include "../../inc/parser.h"

void	print_token(t_token *token)
{
	if (token == NULL)
	{
		ft_printf("NULL\n");
		return ;
	}
	ft_printf("type: %s, value: %s\n",
		convert_ebt_op_to_string(convert_type_to_ebt_op(token->type)),
		token->value);
}

void	print_ebt(t_ebt *ebt, int level)
{
	int	i;

	if (ebt == NULL)
	{
		ft_printf("NULL\n");
		return ;
	}
	ft_printf("\n");
	i = 0;
	while (i++ < level)
		ft_printf(SPACES);
	ft_printf(CYAN_BOLD "EBT_OP: %s\n" RST,
		convert_ebt_op_to_string(ebt->type));
	if (ebt->command)
		print_command(ebt->command, level);
	i = 0;
	while (i++ < level)
		ft_printf(SPACES);
	ft_printf(MAGENTA_BOLD "LEFT -> " RST);
	print_ebt(ebt->left, level + 1);
	i = 0;
	while (i++ < level)
		ft_printf(SPACES);
	ft_printf(BLUE_BOLD "RIGHT -> " RST);
	print_ebt(ebt->right, level + 1);
}

static void	print_command_basic_info(t_command *command, int level)
{
	int	il;

	il = 0;
	while (il++ < level)
		ft_printf(SPACES);
	if (command == NULL)
	{
		ft_printf(GREEN_BOLD "COMMAND NULL\n" RST);
		return ;
	}
	ft_printf(GREEN_BOLD "COMMAND: %s\n" RST, command->command);
	il = 0;
	while (il++ < level)
		ft_printf(SPACES);
	if (command->heredoc_word)
		ft_printf("\theredoc word: %s\n", command->heredoc_word);
}

static void	print_command_args(char **args, int level)
{
	int	i;
	int	il;

	il = 0;
	while (il++ < level)
		ft_printf(SPACES);
	ft_printf("\targs: [");
	i = 0;
	while (args && args[i])
	{
		ft_printf("\"%s\"", args[i++]);
		if (args[i])
			ft_printf(", ");
	}
	ft_printf("]\n");
}

void	print_command(t_command *command, int level)
{
	int		il;
	t_list	*redir;
	t_redir	*r;

	print_command_basic_info(command, level);
	print_command_args(command->args, level);
	redir = command->redirections;
	while (redir)
	{
		r = (t_redir *)redir->content;
		il = 0;
		while (il++ < level)
			ft_printf(SPACES);
		ft_printf("\t{ redir: from: %s\tto: %s\tfilename: %s }\n",
			convert_redir_type_to_string(r->from),
			convert_redir_type_to_string(r->to), r->filename);
		redir = redir->next;
	}
}
