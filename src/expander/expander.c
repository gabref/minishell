#include "../../inc/expander.h"

/*

*/

static int	arg_expander(t_minishell *ms, t_ebt *root)
{
	int	i;

	i = -1;
	while (root->command->args[++i] != NULL)
	{
		if (arg_replace(ms, &root->command->args[i]) == -1)
		{
			return (-1);
		}
	}
	return (0);
}

/*Ritorna 0 se tutto è andato bene*/
static int	find_and_expand(t_ebt *root, t_minishell *ms)
{
	if (root->type != EBT_OP_COMMAND)
	{
		return (1);
	}
	else if (root->type == EBT_OP_COMMAND) // se trovo un comando
	{
		if (arg_expander(ms, root) == -1)
		{
			return (-1);
		}
	}
	return (0);
}

static int	traversal_expander(t_ebt *root, t_minishell *ms)
{
	if (root == NULL)
	{
		return (0);
	}
	if (traversal_expander(root->left, ms) == -1)
	{
		return (-1);
	}
	if (find_and_expand(root, ms) == -1)
	{
		return (-1);
	}
	if (traversal_expander(root->right, ms) == -1)
	{
		return (-1);
	}
	return (0);
}

/*
NOTA: Passo il puntatore alla struct t_minishell e non la struct direttamente
	perchè dovrò modificare il suo elemento t_ebt. Se avessi passato la struct
	avrei in realtà passato una copia e quindi non ne avrei modificato il valore
	(chiamando questa fuzione dovrò dare &ms)

NOTA: Se ritorna -1 l'albero binario non verrà deallocato da questa funzione


*/
int	expander(t_minishell *ms)
{
	if (ms == NULL || ms->ebt == NULL)
		return (-1);
	if (traversal_expander(ms->ebt, ms) == -1)
		return (-1);
	return (0);
}
