/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:04:19 by cmaestri          #+#    #+#             */
/*   Updated: 2024/08/06 18:34:21 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/colors.h"
#include "../../inc/expander.h"
#include "../../inc/input.h"
#include "../../inc/parser.h"
#include "../../inc/utils.h"

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
	tmp = ft_strjoin(MAGENTA "", pwd);
	final = ft_strjoin(tmp, RST BLACK "");
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
	tmp[3] = ft_strjoin(tmp[2], "@ms" WHITE);
	if (ms->last_exit_status != 0)
		tmp[4] = ft_strjoin(tmp[1], RED);
	else
		tmp[4] = ft_strjoin(tmp[1], GREEN);
	tmp[5] = ft_strjoin(tmp[3], tmp[4]);
	prompt = ft_strjoin(tmp[5], " $> " RST);
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
	prompt = create_prompt(ms);
	input = readline("$> ");
	free(prompt);
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

bool	handle_input(t_minishell *ms, char *input)
{
	t_lexer	*lex;
	t_ebt	*parser;

	if (string_all_spaces(input))
		free_and_return_bool(input, true);
	lex = lexer(input);
	if (!lex)
	{
		ft_printf(RED "lexer error\n" RST);
		free_and_return_bool(input, false);
	}
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
