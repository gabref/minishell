/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:26:57 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/25 00:16:58 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "minishell.h"

t_ebt	*parse(t_minishell *ms, t_lexer *lexer);
void	print_ebt(t_ebt *ebt, int level);
void	free_ebt(t_ebt *ebt);

#endif
