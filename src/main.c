# include "../inc/minishell.h"

int main(void)
{
	t_minishell ms;

	init_minishell(&ms);
	destroy_minishell(&ms);
	return (0);
}
