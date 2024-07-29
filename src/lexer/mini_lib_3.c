#include "../../inc/lexer.h"

int	ft_isalnum_lex(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9'));
}

int	ft_isprint_lex(int c)
{
	return (c > 32 && c <= 126);
}

void	recur_list_dalloc(t_token **root)
{
	t_token	*curr;
	t_token	*temp;

	if (*root == NULL)
		return ;
			/*Questo per evitare di cancellare cose se passo un nodo nullo*/
	curr = *root;
	temp = curr;
	curr = curr->next;
	free(temp->value);
	free(temp);
	if (curr != NULL)
		recur_list_dalloc(&curr);
	*root = NULL;
}

int	add_end(t_token **ret, char *str, int start, int end, t_token_type type)
{
	t_token	*curr;
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (1);
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
