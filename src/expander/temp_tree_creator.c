#include "../../inc/expander.h"

void	printtree(t_ebt *root)
{
	int	i;

	i = 0;
	if (root == NULL)
	{
		printf("---<empty>---\n");
		return ;
	}
	printf("value = %s\n", root->command->command);
	/*******************/
	if (!(*root->command->args))
		printf("args = NULL\n");
	/*******************/
	while (root->command->args[i])
	{
		printf("args = %s\n", root->command->args[i]);
		i++;
	}
	printf("type = %d\n", root->type);
	printf("\n");
	printtree(root->left);
	printtree(root->right);
}

void	free_tree(t_ebt *root)
{
	int	i;

	if (root == NULL)
		return ;
	// Libera i sottoalberi sinistro e destro
	free_tree(root->left);
	free_tree(root->right);
	// Libera la struttura command e i suoi membri
	if (root->command != NULL)
	{
		free(root->command->command);
		free(root->command->heredoc_file_name);
		if (root->command->args != NULL)
		{
			i = 0;
			while (root->command->args[i])
			{
				free(root->command->args[i]);
				i++;
			}
			free(root->command->args);
		}
		free(root->command);
	}
	// Infine, libera il nodo stesso
	free(root);
}

/*Questa funzione alloca:
- un nodo dell'albero
- la struct command
- il comando
- la matrice degli argomenti
- il nome del file heredoc
*/
static t_ebt	*createnode(int len_cmd, int len_args, int len_heredoc)
{
	t_ebt	*result;

	result = malloc(sizeof(t_ebt));
	if (result != NULL)
	{
		result->command = malloc(sizeof(t_command));
		if (result->command != NULL)
		{
			result->command->command = malloc(sizeof(char) * (len_cmd + 1));
			if (result->command->command != NULL)
			{
				result->command->args = malloc(sizeof(char *) * (len_args + 1));
				if (result->command->args != NULL)
				{
					result->command->heredoc_file_name = malloc(sizeof(char)
							* (len_heredoc + 1));
					if (result->command->heredoc_file_name == NULL)
					{
						free(result->command->args);
						free(result->command->command);
						free(result->command);
						free(result);
						result = NULL;
					}
				}
				else
				{
					free(result->command->command);
					free(result->command);
					free(result);
					result = NULL;
				}
			}
			else
			{
				free(result->command);
				free(result);
				result = NULL;
			}
		}
		else
		{
			free(result);
			result = NULL;
		}
	}
	return (result);
}

/*Con quesya funzione riempio il nodo.
NOTE: - La matrice degli argomenti ha dimensione fissa = 1
*/
static t_ebt	*fill_node(int len_cmd, char *cmd, int len_arg_1, char *arg_1,
		int len_arg_2, char *arg_2, int len_heredoc, char *heredoc, int type)
{
	t_ebt	*result;

	result = createnode(len_cmd, 2, len_heredoc);
	if (result != NULL)
	{
		if (result->command->command)
			ft_strlcpy(result->command->command, cmd, len_cmd + 1);
		result->command->args[0] = (char *)malloc(sizeof(char) * (len_arg_1
					+ 1));
		if (result->command->args[0])
		{
			ft_strlcpy(result->command->args[0], arg_1, len_arg_1 + 1);
		}
		result->command->args[1] = (char *)malloc(sizeof(char) * (len_arg_2
					+ 1));
		if (result->command->args[1])
			ft_strlcpy(result->command->args[1], arg_2, len_arg_2 + 1);
		result->command->args[2] = NULL;
		if (result->command->heredoc_file_name)
			ft_strlcpy(result->command->heredoc_file_name, heredoc, len_heredoc
				+ 1);
		result->type = type;
		result->left = NULL;
		result->right = NULL;
	}
	return (result);
}

void	create_ebt_test(t_ebt **ebt)
{
	*ebt = fill_node(2, "||", 0, "\0", 0, "\0", 0, "\0", EBT_OP_OR);
	(*ebt)->left = fill_node(2, "&&", 0, "\0", 0, "\0", 0, "\0", EBT_OP_AND);
	(*ebt)->right = fill_node(1, "|", 0, "\0", 0, "\0", 0, "\0", EBT_OP_PIPE);
	(*ebt)->left->left = fill_node(4, "echo", 2, "-l", 2, "-c", 0, "\0",
			EBT_OP_COMMAND);
	(*ebt)->left->right = fill_node(4, "echo", 10, "$HOME/ciao", 1, "l", 0,
			"\0", EBT_OP_COMMAND);
	(*ebt)->right->left = fill_node(2, "ls", 2, "-a", 1, "f", 0, "\0",
			EBT_OP_COMMAND);
	(*ebt)->right->right = fill_node(4, "(ls)", 0, "\0", 0, "\0", 0, "\0",
			EBT_OP_SUBSHELL);
	(*ebt)->right->right->left = fill_node(1, ";", 0, "\0", 0, "\0", 0, "\0",
			EBT_OP_SEMICOLON);
	(*ebt)->right->right->right = fill_node(1, "echo", 5, "Mak*", 1, "l", 0,
			"\0", EBT_OP_COMMAND);
}
