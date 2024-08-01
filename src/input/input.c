/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:04:19 by cmaestri          #+#    #+#             */
/*   Updated: 2024/08/01 16:42:36 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/expander.h"
#include "../../inc/input.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include <unistd.h>

// funzione per pulire lo schermo se l'utente scrive "clear"
void	clean_screen(void)
{
	write(STDOUT_FILENO, "\033[H\033[J", 6);
}

char	*get_prompt_cd(t_minishell *ms)
{
	char	*tmp;
	char	*pwd;
	char	*home;
	char	*final;

	pwd = ms_get_env(ms, "PWD");
	if (!pwd)
		return (strdup("___"));
	home = ms_get_env(ms, "HOME");
	if (!home)
		return (strdup("___"));
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
		substitute_str(&pwd, 0, ft_strlen(home), "~");
	free(home);
	tmp = ft_strjoin(MAGENTA " 󰝰  ", pwd);
	final = ft_strjoin(tmp, RST BLACK "");
	free(pwd);
	free(tmp);
	return (final);
}

char	*get_prompt_user(t_minishell *ms)
{
	char	*tmp;
	char	*user;

	user = ms_get_env(ms, "USER");
	if (!user)
		return (strdup("___"));
	if (ft_strncmp(user, "root", 4) == 0)
		tmp = ft_strdup(RED "root" RST);
	else
		tmp = ft_strjoin(BLUE, user);
	free(user);
	return (tmp);
}

char	*create_prompt(t_minishell *ms)
{
	char	*tmp[6];
	char	*prompt;

	tmp[0] = get_prompt_user(ms);
	tmp[1] = get_prompt_cd(ms);
	tmp[2] = ft_strjoin(BLACK BBLACK, tmp[0]);
	tmp[3] = ft_strjoin(tmp[2], "@ms 󰄛" WHITE " ");
	if (ms->last_exit_status != 0)
		tmp[4] = ft_strjoin(tmp[1], RED);
	else
		tmp[4] = ft_strjoin(tmp[1], GREEN);
	tmp[5] = ft_strjoin(tmp[3], tmp[4]);
	prompt = ft_strjoin(tmp[5], "$> " RST);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	free(tmp[4]);
	free(tmp[5]);
	return (prompt);
}

char	*get_input(t_minishell *ms)
{
	char	*input;
	char	*prompt;

	if (ms->ebt)
		free_ebt(ms->ebt);
	ms->ebt = NULL;
	(void)prompt;
	// prompt = create_prompt(ms);
	input = readline("$> ");
	// free(prompt);
	if (input == NULL)
		return (NULL);
	if (input[0] == '\0')
	{
		free(input);
		return (ft_strdup(" "));
	}
	if (input[0] == EOF)
	{
		free(input);
		return (NULL);
	}
	if (input[0] != '\0')
		ms_append_history(ms, input);
	return (input);
}

void	test_print_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token->value == NULL)
	{
		ft_printf("token is NULL\n");
		return ;
	}
	printf("token value:\t%s,\ttype: %d,\tstart idx: %d,\tcurrent idx: %d\n",
		token->value, token->type, token->input_start_idx, token->current_idx);
}

void	ms_print_lexer(t_lexer *lex)
{
	if (!lex)
	{
		ft_printf("no lexer\n");
		return ;
	}
	ft_printf("size: %d\n", lex->size);
	ft_lstiter(lex->tokens, test_print_token);
}

bool	string_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
			return (false);
		i++;
	}
	return (true);
}

bool	handle_input(t_minishell *ms, char *input)
{
	t_lexer	*lex;
	t_ebt	*parser;

	if (string_all_spaces(input))
	{
		free(input);
		return (true);
	}
	lex = lexer(input);
	if (!lex)
	{
		ft_printf(RED "lexer error\n" RST);
		free(input);
		return (false);
	}
	// ms_print_lexer(lex);
	free(input);
	expander(ms, lex);
	parser = parse(ms, lex);
	free_lexer(lex);
	if (!parser)
	{
		ft_printf(RED "parser error\n" RST);
		return (1);
	}
	ms->ebt = parser;
	return (true);
}
