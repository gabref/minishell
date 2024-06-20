/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:36:04 by galves-f          #+#    #+#             */
/*   Updated: 2024/06/20 14:52:05 by galves-f         ###   ########.fr       */
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

	// add_end(&lexer->tokens, ft_strdup("netstat"), 0, 6, WORD);
	// add_end(&lexer->tokens, ft_strdup("-an"), 7, 10, WORD);
	// add_end(&lexer->tokens, ft_strdup("|"), 11, 11, PIPE);
	// add_end(&lexer->tokens, ft_strdup("grep"), 13, 16, WORD);
	// add_end(&lexer->tokens, ft_strdup("'ESTABLISHED'"), 17, 29, WORD);
	// add_end(&lexer->tokens, ft_strdup(">"), 31, 31, OUT_APPEND);
	// add_end(&lexer->tokens, ft_strdup("/tmp/established_connections.txt"), 33, 64, WORD);
	// add_end(&lexer->tokens, ft_strdup("&&"), 66, 67, AND);
	// add_end(&lexer->tokens, ft_strdup("echo"), 69, 72, WORD);
	// add_end(&lexer->tokens, ft_strdup("\"Connections listed successfully\""), 73, 102, WORD);
	// add_end(&lexer->tokens, ft_strdup(">"), 104, 104, OUT_APPEND);
	// add_end(&lexer->tokens, ft_strdup("/var/log/netstat.log"), 106, 126, WORD);
	// add_end(&lexer->tokens, ft_strdup("||"), 128, 129, OR);
	// add_end(&lexer->tokens, ft_strdup("echo"), 131, 134, WORD);
	// add_end(&lexer->tokens, ft_strdup("\"Failed to list connections\""), 135, 162, WORD);
	// add_end(&lexer->tokens, ft_strdup(">"), 164, 164, OUT_APPEND);
	// add_end(&lexer->tokens, ft_strdup("/var/log/netstat_error.log"), 166, 191, WORD);
	// add_end(&lexer->tokens, ft_strdup(";"), 192, 192, SEMICOLON);

	// df -h | grep '/dev/sda1' | awk '{print $5}' | sed 's/%//' | { read usage; echo "Disk usage: $usage%" > /var/log/disk_usage.log; [ $usage -gt 90 ] && echo "Alert: High disk usage" | mail -s "Disk Usage Alert" admin@example.com; };
	// add_end(&lexer->tokens, ft_strdup("df"), 0, 1, WORD);
	// add_end(&lexer->tokens, ft_strdup("-h"), 3, 4, WORD);
	// add_end(&lexer->tokens, ft_strdup("|"), 6, 6, PIPE);
	// add_end(&lexer->tokens, ft_strdup("grep"), 8, 11, WORD);
	// add_end(&lexer->tokens, ft_strdup("'/dev/sda1'"), 13, 24, WORD);
	// add_end(&lexer->tokens, ft_strdup("|"), 26, 26, PIPE);
	// add_end(&lexer->tokens, ft_strdup("awk"), 28, 31, WORD);
	// add_end(&lexer->tokens, ft_strdup("'{print $5}'"), 33, 45, WORD);
	// add_end(&lexer->tokens, ft_strdup("|"), 47, 47, PIPE);
	// add_end(&lexer->tokens, ft_strdup("sed"), 49, 52, WORD);
	// add_end(&lexer->tokens, ft_strdup("'s/%//'"), 54, 61, WORD);
	// add_end(&lexer->tokens, ft_strdup("|"), 63, 63, PIPE);
	// add_end(&lexer->tokens, ft_strdup("{"), 65, 65, O_PARENTHESES);
	// add_end(&lexer->tokens, ft_strdup("read"), 67, 70, WORD);
	// add_end(&lexer->tokens, ft_strdup("usage"), 72, 77, WORD);
	// add_end(&lexer->tokens, ft_strdup(";"), 78, 78, SEMICOLON);
	// add_end(&lexer->tokens, ft_strdup("echo"), 80, 83, WORD);
	// add_end(&lexer->tokens, ft_strdup("\"Disk usage: $usage%\""), 84, 103, WORD);
	// add_end(&lexer->tokens, ft_strdup(">"), 105, 105, OUT_APPEND);
	// add_end(&lexer->tokens, ft_strdup("/var/log/disk_usage.log"), 107, 130, WORD);
	// add_end(&lexer->tokens, ft_strdup(";"), 131, 131, SEMICOLON);
	// add_end(&lexer->tokens, ft_strdup("["), 133, 133, O_PARENTHESES);
	// add_end(&lexer->tokens, ft_strdup("$usage"), 135, 140, WORD);
	// add_end(&lexer->tokens, ft_strdup("-gt"), 142, 144, WORD);
	// add_end(&lexer->tokens, ft_strdup("90"), 146, 147, WORD);
	// add_end(&lexer->tokens, ft_strdup("]"), 148, 148, C_PARENTHESES);
	// add_end(&lexer->tokens, ft_strdup("&&"), 150, 151, AND);
	// add_end(&lexer->tokens, ft_strdup("echo"), 153, 156, WORD);
	// add_end(&lexer->tokens, ft_strdup("\"Alert: High disk usage\""), 157, 181, WORD);
	// add_end(&lexer->tokens, ft_strdup("|"), 183, 183, PIPE);
	// add_end(&lexer->tokens, ft_strdup("mail"), 185, 188, WORD);
	// add_end(&lexer->tokens, ft_strdup("-s"), 190, 191, WORD);
	// add_end(&lexer->tokens, ft_strdup("\"Disk Usage Alert\""), 193, 210, WORD);
	// add_end(&lexer->tokens, ft_strdup("admin@example.com"), 212, 228, WORD);
	// add_end(&lexer->tokens, ft_strdup(";"), 229, 229, SEMICOLON);
	// add_end(&lexer->tokens, ft_strdup("}"), 231, 231, C_PARENTHESES);
	// add_end(&lexer->tokens, ft_strdup(";"), 232, 232, SEMICOLON);

	// (cd ciao && ls || echo "cd didn work")
	// add_end(&lexer->tokens, ft_strdup("("), 0, 0, O_PARENTHESES);
	// add_end(&lexer->tokens, ft_strdup("cd"), 1, 2, WORD);
	// add_end(&lexer->tokens, ft_strdup("ciao"), 4, 7, WORD);
	// add_end(&lexer->tokens, ft_strdup("&&"), 9, 10, AND);
	// add_end(&lexer->tokens, ft_strdup("ls"), 12, 13, WORD);
	// add_end(&lexer->tokens, ft_strdup("||"), 15, 16, OR);
	// add_end(&lexer->tokens, ft_strdup("echo"), 18, 21, WORD);
	// add_end(&lexer->tokens, ft_strdup("\"cd didn work\""), 23, 36, WORD);
	// add_end(&lexer->tokens, ft_strdup(")"), 37, 37, C_PARENTHESES);

	// (date -u) | sed -e 's/ /     /g'
	add_end(&lexer->tokens, ft_strdup("("), 0, 0, O_PARENTHESES);
	add_end(&lexer->tokens, ft_strdup("date"), 1, 4, WORD);
	add_end(&lexer->tokens, ft_strdup("-u"), 6, 7, WORD);
	add_end(&lexer->tokens, ft_strdup(")"), 8, 8, C_PARENTHESES);
	add_end(&lexer->tokens, ft_strdup("|"), 10, 10, PIPE);
	add_end(&lexer->tokens, ft_strdup("sed"), 12, 15, WORD);
	add_end(&lexer->tokens, ft_strdup("-e"), 17, 18, WORD);
	add_end(&lexer->tokens, ft_strdup("'s/ /     /g'"), 20, 32, WORD);

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
