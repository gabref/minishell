#include "../../inc/lexer.h"

void	free_and_quit(t_lexer *lexer, char *token)
{
	if (token != NULL)
		free(token);
	if (lexer->tokens != NULL)
		recur_list_dalloc(&(lexer->tokens));
	free(lexer);
}

int	init_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
	{
		return (1);
	}
	lexer->tokens = NULL;
	lexer->size = 0;
	return (0);
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

/* DA CANCELLARE */
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
