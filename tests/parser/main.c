/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:36:04 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/25 12:06:14 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/lexer.h"
#include "../../inc/minishell.h"
#include "../../inc/utils.h"
#include "../../inc/parser.h"
#include "../../inc/expander.h"

void	ms_print_lexer(t_lexer *lex);

void	lexer_tests(t_minishell *ms)
{
	t_lexer	*lex;
	t_ebt 	*parser;

	// lex = lexer("netstat -an | grep 'ESTABLISHED' > /tmp/established_connections.txt && echo \"Connections listed successfully\" > /var/log/netstat.log || echo \"Failed to list connections\" > /var/log/netstat_error.log");
	// lex = lexer("(date -u) | sed -e 's/ /     /g'");
	// lex = lexer("(cd ciao && ls || echo \"cd didn work\")");
	// lex = lexer("(({ ls; }))");
	lex = lexer("echo ciao$USER > temp.txt");
	// lex = lexer(";;");
	// lex = lexer("echo ciao << bella > ciao >> myfile && cat < myfile; ls >> myfile > ciao < myfile");
	// lex = lexer("<< bella > myfile");
	// lex = lexer("> cool_file");
	// lex = lexer(">");
	// lex = lexer("cd $(pwd)");

	ms_print_lexer(lex);
	parser = parse(ms, lex);
	free_lexer(lex);
	ms->ebt = parser;
	print_ebt(ms->ebt, 0);
	expander(ms);
	print_ebt(ms->ebt, 0);
}

void	ms_print_lexer(t_lexer *lex)
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
		ft_printf("token value:\t%s,\ttype: %d,\tstart idx: %d,\tcurrent idx: %d\n",
			current->value, current->type, current->input_start_idx,
			current->current_idx);
		current = current->next;
	}
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
