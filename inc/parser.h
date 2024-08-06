/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:26:57 by galves-f          #+#    #+#             */
/*   Updated: 2024/08/06 15:01:10 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "minishell.h"

t_ebt		*parse(t_minishell *ms, t_lexer *lexer);
t_ebt		*parse_expr(t_minishell *ms, t_list **tokens);
t_ebt		*parse_command(t_minishell *ms, t_list **tokens);

t_ebt		*create_ebt(void);
char		*convert_redir_type_to_string(t_red_type type);
char		*convert_ebt_op_to_string(t_ebt_op type);
t_ebt_op	convert_type_to_ebt_op(t_token_type type);

void		print_token(t_token *token);
void		print_command(t_command *command, int level);
void		print_ebt(t_ebt *ebt, int level);

void		free_redirection(void *ptr);
void		free_command(t_command *command);
void		free_ebt(t_ebt *ebt);

int			is_open_parenthesis(t_token *token);
int			is_close_parenthesis(t_token *token);
int			is_primary_token(t_token *token);
int			is_angle_bracket(t_token *token);
int			is_binary_token_semicolon(t_token *token);
int			is_binary_token(t_token *token);

int			not_eof(t_token *token);
t_token		*peek(t_list *tokens);
t_token		*eat(t_list **tokens);
void		*expect(t_minishell *ms, t_list **tokens, t_token_type type,
				char *err_message);

#endif
