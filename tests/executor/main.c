#include "../../inc/colors.h"
#include "../../inc/lexer.h"
#include "../../inc/minishell.h"
#include "../../inc/utils.h"
#include "../../inc/parser.h"
#include "../../inc/expander.h"

void	lexer_tests(t_minishell *ms)
{
	t_lexer	*lex;
	t_ebt 	*parser;

	lex = lexer("(date -u) | sed -e 's/ /     /g'");
	// lex = lexer("(cd ciao && ls || echo \"cd didn work\")");
	// lex = lexer("(({ ls; }))");
	// lex = lexer(";;");
	// lex = lexer("echo ciao << bella > ciao >> myfile && cat < myfile; ls >> myfile > ciao < myfile");
	// lex = lexer("<< bella > myfile");
	// lex = lexer("> cool_file");
	// lex = lexer(">");
	// lex = lexer("cd $(pwd)");
	// lex = lexer("mkdir -p src ciao bella oi && ls -l src && echo \"ciao\" || echo \"bella\" | echo \"oi\" && echo \"\"");
	// lex = lexer("ls $PWD/$PATH/ciao $USER '$USER' \"$USER\" \"\\$USER\" ciao$USER \\$USER && ls $PD/$PTH/ciao $USR '$USR' \"$USR\" \"\\$USR\" ciao$USR \\$USR");
	// lex = lexer("ls ciao/$PD $?");

	expander(ms, lex);
	parser = parse(ms, lex);
	free_lexer(lex);
	ms->ebt = parser;
	print_ebt(ms->ebt, 0);

	// TODO EXECUTOR
	// execute(ms, parser);
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
