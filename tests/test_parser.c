#include "../inc/minishell.h"
#include "../inc/lexer.h"
#include "../inc/utils.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

t_lexer	*l;

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

void suite_setup(void)
{
	l = safe_malloc(sizeof(t_lexer));
	l->size = 0;
	l->tokens = NULL;
}

void suite_teardown(void)
{
	free_lexer(l);
}

TestSuite(parser, .init=suite_setup, .fini=suite_teardown);

Test(parser, simple_case)
{
	add_end(&l->tokens, ft_strdup("echo"), 0, 3, WORD);
	add_end(&l->tokens, ft_strdup("hello"), 5, 9, WORD);
	add_end(&l->tokens, ft_strdup("world"), 11, 15, WORD);
	add_end(&l->tokens, ft_strdup(">"), 17, 18, OUT_APPEND);
	add_end(&l->tokens, ft_strdup("file.txt"), 19, 27, WORD);
	add_end(&l->tokens, ft_strdup("2>"), 29, 31, OUT_APPEND);
	add_end(&l->tokens, ft_strdup("error.txt"), 32, 41, WORD);
	cr_assert_not_null(l->tokens);
}
