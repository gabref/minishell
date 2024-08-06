/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:53:21 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 13:55:03 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	test_print_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token->value == NULL)
	{
		ft_printf("token is NULL\n");
		return ;
	}
	printf("token value:\t%s,\ttype: %d,\tstart idx: %d,\tcurrent idx: %d\n",
		token->value, token->type, token->input_start_idx, token->current_idx);
}

void	ms_print_lexer(t_lexer *lex)
{
	if (!lex)
	{
		ft_printf("no lexer\n");
		return ;
	}
	ft_printf("size: %d\n", lex->size);
	ft_lstiter(lex->tokens, test_print_token);
}
