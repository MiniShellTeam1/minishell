/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:09 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 13:22:10 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

# include "lexer.h"

int handle_normal(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int handle_single_quote(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int handle_double_quote(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int handle_word(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int handle_operator(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);

#endif