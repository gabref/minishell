/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:27:01 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/15 13:05:05 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	append_history(t_minishell *ms, char *line)
{
	t_list	*node;
	t_list	*new_node;

	node = ms->history.inputs;
	while (node)
	{
		if (ft_strncmp((char *)node->content, line, ft_strlen(line)) == 0)
			return ;
		node = node->next;
	}
	new_node = ft_lstnew(ft_strdup(line));
	if (!new_node)
		return ;
	ft_lstadd_front(&ms->history.inputs, new_node);
	ms->history.cur_idx++;
}

char	*get_history_idx(t_minishell *ms, int idx)
{
	t_list	*node;
	int		i;

	node = ms->history.inputs;
	i = 0;
	while (node)
	{
		if (i == idx)
			return ((char *)node->content);
		node = node->next;
		i++;
	}
	return (NULL);
}

void	destroy_history(t_minishell *ms)
{
	if (ms->history.inputs != NULL)
		ft_lstclear(&ms->history.inputs, free);
}

void	print_history(t_minishell *ms)
{
	t_list	*node;
	int		i;

	ft_printf("\nminishell history\n   -----------\n");
	node = ms->history.inputs;
	i = 0;
	while (node)
	{
		ft_printf("%d: %s\n", i++, (char *)node->content);
		node = node->next;
	}
	ft_printf("\n");
}
