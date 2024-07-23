/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:13:01 by galves-f          #+#    #+#             */
/*   Updated: 2024/07/11 17:10:47 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZERS_H
# define INITIALIZERS_H

# include "../libs/libft/inc/libft.h"
# include "lexer.h"
# include "minishell.h"

/* get list of important env variables */
t_list	*get_env_list(char **env);
void	get_input(t_minishell *ms, t_lexer *lex);
void	destroy_history(t_minishell *ms);

#endif
