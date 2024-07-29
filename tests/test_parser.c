#include "../inc/minishell.h"
#include "../inc/lexer.h"
#include "../inc/utils.h"
#include "../inc/parser.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

t_lexer	*l;
t_ebt 	*ebt;
t_minishell ms;

void suite_setup(void)
{
	init_minishell(&ms, NULL);
	l = safe_malloc(sizeof(t_lexer));
	l->size = 0;
	l->tokens = NULL;
}

void suite_teardown(void)
{
	free_lexer(l);
	free_ebt(ebt);
	destroy_minishell(&ms);
}

TestSuite(parser, .init=suite_setup, .fini=suite_teardown);

Test(parser, simple_case)
{
	l = lexer("echo ciao > temp.txt");
	ebt = parse(&ms, l);
	cr_assert_not_null(ebt);
	cr_assert_str_eq(ebt->command->command, "echo");
	cr_assert_str_eq(((t_redir *) ebt->command->redirections->content)->filename, "temp.txt");
	cr_assert_eq(((t_redir *) ebt->command->redirections->content)->from, RT_STDOUT);
	cr_assert_eq(((t_redir *) ebt->command->redirections->content)->to, RT_WRITE);
}

Test(parser, redirections_cases)
{
	l = lexer("echo ciao << bella > ciao >> myfile && cat < myfile; ls >> myfile > ciao < myfile");
	ebt = parse(&ms, l);
	cr_assert_not_null(ebt);
	cr_assert_eq(ebt->command, NULL);
	cr_assert_eq(ebt->type, EBT_OP_SEMICOLON);
	cr_assert_eq(ebt->left->type, EBT_OP_AND);
	cr_assert_eq(ebt->left->left->type, EBT_OP_COMMAND);
	cr_assert_eq(ebt->left->left->command->heredoc, true);
	cr_assert_str_eq(ebt->left->left->command->heredoc_word, "bella");
	cr_assert_str_eq(ebt->left->left->command->command, "echo");
	cr_assert_str_eq(*(ebt->left->left->command->args), "ciao");
	cr_assert_str_eq(((t_redir *)ebt->left->left->command->redirections->content)->filename, "ciao");
	cr_assert_eq(((t_redir *)ebt->left->left->command->redirections->content)->from, RT_STDOUT);
	cr_assert_eq(((t_redir *)ebt->left->left->command->redirections->content)->to, RT_WRITE);
	cr_assert_str_eq(((t_redir *)ebt->left->left->command->redirections->next->content)->filename, "myfile");
	cr_assert_eq(((t_redir *)ebt->left->left->command->redirections->next->content)->from, RT_STDOUT);
	cr_assert_eq(((t_redir *)ebt->left->left->command->redirections->next->content)->to, RT_APPEND);
	cr_assert_str_eq(ebt->left->right->command->command, "cat");
	cr_assert_str_eq(((t_redir *)ebt->left->right->command->redirections->content)->filename, "myfile");
	cr_assert_eq(((t_redir *)ebt->left->right->command->redirections->content)->from, RT_READ);
	cr_assert_eq(((t_redir *)ebt->left->right->command->redirections->content)->to, RT_STDIN);
}

Test(parser, subshell_case)
{
	l = lexer("(date -u) | sed -e 's/ /     /g'");
	ebt = parse(&ms, l);
	cr_assert_not_null(ebt);
	cr_assert_eq(ebt->command, NULL);
	cr_assert_eq(ebt->type, EBT_OP_PIPE);
	cr_assert_eq(ebt->left->type, EBT_OP_SUBSHELL);
	cr_assert_eq(ebt->left->left->type, EBT_OP_COMMAND);
	cr_assert_str_eq(ebt->left->left->command->command, "date");
	cr_assert_str_eq(*(ebt->left->left->command->args), "-u");
	cr_assert_eq(ebt->left->right, NULL);
	cr_assert_str_eq(ebt->right->command->command, "sed");
	cr_assert_str_eq(*(ebt->right->command->args), "-e");
	cr_assert_str_eq(*(ebt->right->command->args + 1), "'s/ /     /g'");
}

Test(parser, and_or_case)
{
	l = lexer("(cd ciao && ls || echo \"cd didn work\")");
	ebt = parse(&ms, l);
	cr_assert_not_null(ebt);
	cr_assert_eq(ebt->command, NULL);
	cr_assert_eq(ebt->type, EBT_OP_SUBSHELL);
	cr_assert_eq(ebt->left->type, EBT_OP_OR);
	cr_assert_eq(ebt->left->left->type, EBT_OP_AND);
	cr_assert_eq(ebt->left->left->left->type, EBT_OP_COMMAND);
	cr_assert_str_eq(ebt->left->left->left->command->command, "cd");
	cr_assert_str_eq(*(ebt->left->left->left->command->args), "ciao");
	cr_assert_eq(ebt->left->left->right->type, EBT_OP_COMMAND);
	cr_assert_str_eq(ebt->left->left->right->command->command, "ls");
	cr_assert_eq(ebt->left->right->type, EBT_OP_COMMAND);
	cr_assert_str_eq(ebt->left->right->command->command, "echo");
	cr_assert_str_eq(*(ebt->left->right->command->args), "\"cd didn work\"");
}

Test(parser, subshell_case_2)
{
	l = lexer("(({ ls; }))");
	ebt = parse(&ms, l);
	cr_assert_not_null(ebt);
	cr_assert_eq(ebt->command, NULL);
	cr_assert_eq(ebt->type, EBT_OP_SUBSHELL);
	cr_assert_eq(ebt->left->type, EBT_OP_SUBSHELL);
	cr_assert_eq(ebt->left->left->type, EBT_OP_SUBSHELL);
	cr_assert_eq(ebt->left->left->left->type, EBT_OP_COMMAND);
	cr_assert_str_eq(ebt->left->left->left->command->command, "ls");
}

Test(parser, heredoc_simple)
{
	l = lexer("<< bella > myfile");
	ebt = parse(&ms, l);
	cr_assert_not_null(ebt);
	cr_assert_eq(ebt->command->command, NULL);
	cr_assert_eq(ebt->type, EBT_OP_COMMAND);
	cr_assert_eq(ebt->command->heredoc, true);
	cr_assert_str_eq(ebt->command->heredoc_word, "bella");
	cr_assert_str_eq(((t_redir *)ebt->command->redirections->content)->filename, "myfile");
	cr_assert_eq(((t_redir *)ebt->command->redirections->content)->from, RT_STDOUT);
	cr_assert_eq(((t_redir *)ebt->command->redirections->content)->to, RT_WRITE);
}

Test(parser, simple_redir)
{
	l = lexer("> cool_file");
	ebt = parse(&ms, l);
	cr_assert_not_null(ebt);
	cr_assert_eq(ebt->command->command, NULL);
	cr_assert_eq(ebt->type, EBT_OP_COMMAND);
	cr_assert_str_eq(((t_redir *)ebt->command->redirections->content)->filename, "cool_file");
	cr_assert_eq(((t_redir *)ebt->command->redirections->content)->from, RT_STDOUT);
	cr_assert_eq(((t_redir *)ebt->command->redirections->content)->to, RT_WRITE);
}

Test(parser, simple_redir_2)
{
	l = lexer(">");
	ebt = parse(&ms, l);
	cr_assert_eq(ebt, NULL);
}

Test(parser, semicolon_case)
{
	l = lexer(";;");
	ebt = parse(&ms, l);
	cr_assert_eq(ebt, NULL);
}
