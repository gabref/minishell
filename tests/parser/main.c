/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:36:04 by galves-f          #+#    #+#             */
/*   Updated: 2024/06/14 19:01:24 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/lexer.h"
#include "../../inc/minishell.h"
#include "../../inc/utils.h"
#include "../../inc/parser.h"

void	lexer_tests(t_minishell *ms)
{
	t_lexer	*lexer;

	lexer = safe_malloc(sizeof(t_lexer));
	lexer->size = 0;
	lexer->tokens = NULL;

	// netstat -an | grep 'ESTABLISHED' > /tmp/established_connections.txt && echo "Connections listed successfully" > /var/log/netstat.log || echo "Failed to list connections" > /var/log/netstat_error.log;

	add_end(&lexer->tokens, ft_strdup("netstat"), 0, 6, WORD);
	add_end(&lexer->tokens, ft_strdup("-an"), 7, 10, WORD);
	add_end(&lexer->tokens, ft_strdup("|"), 11, 11, PIPE);
	add_end(&lexer->tokens, ft_strdup("grep"), 13, 16, WORD);
	add_end(&lexer->tokens, ft_strdup("'ESTABLISHED'"), 17, 29, WORD);
	add_end(&lexer->tokens, ft_strdup(">"), 31, 31, OUT_APPEND);
	add_end(&lexer->tokens, ft_strdup("/tmp/established_connections.txt"), 33, 64, WORD);
	add_end(&lexer->tokens, ft_strdup("&&"), 66, 67, AND);
	add_end(&lexer->tokens, ft_strdup("echo"), 69, 72, WORD);
	add_end(&lexer->tokens, ft_strdup("\"Connections listed successfully\""), 73, 102, WORD);
	add_end(&lexer->tokens, ft_strdup(">"), 104, 104, OUT_APPEND);
	add_end(&lexer->tokens, ft_strdup("/var/log/netstat.log"), 106, 126, WORD);
	add_end(&lexer->tokens, ft_strdup("||"), 128, 129, OR);
	add_end(&lexer->tokens, ft_strdup("echo"), 131, 134, WORD);
	add_end(&lexer->tokens, ft_strdup("\"Failed to list connections\""), 135, 162, WORD);
	add_end(&lexer->tokens, ft_strdup(">"), 164, 164, OUT_APPEND);
	add_end(&lexer->tokens, ft_strdup("/var/log/netstat_error.log"), 166, 191, WORD);
	add_end(&lexer->tokens, ft_strdup(";"), 192, 192, SEMICOLON);

	// print_lexer(lexer);
	parse(ms, lexer);

	free_lexer(lexer);
}

int	add_end(t_token **ret, char *str, int start, int end, t_token_type type)
{
	t_token	*curr;
	t_token	*new_node;

	new_node = safe_malloc(sizeof(t_token));
	new_node->next = NULL;
	new_node->value = str;
	new_node->input_start_idx = start;
	new_node->current_idx = end;
	new_node->type = type;
	if (*ret == NULL)
	{
		*ret = new_node;
		return (0);
	}
	curr = *ret;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
	return (0);
}
void	print_lexer(t_lexer *lex)
{
	t_token	*current;

	if (!lex)
	{
		ft_printf("no lexer\n");
		return ;
	}
	current = lex->tokens;
	ft_printf("size: %d\n", lex->size);
	while (current->next)
	{
		ft_printf("token value: %s, type: %d, start idx: %d, current idx: %d\n",
			current->value, current->type, current->input_start_idx,
			current->current_idx);
		current = current->next;
	}
}
void	free_lexer(t_lexer *lex)
{
	t_token	*current;
	t_token	*next;

	current = lex->tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	free(lex);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	if (ac != 1 || av[1])
	{
		ft_printf(RED MSG_ERR_ARGS RST);
		exit(EXIT_FAILURE);
	}
	(void)envp;
	init_minishell(&ms, NULL);
	lexer_tests(&ms);
	destroy_minishell(&ms);
	return (0);
}
