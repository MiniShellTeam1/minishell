/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 15:30:00 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_double_quote(t_lexer_data *data)
{
	debug_lexer_step(data, "ENTERING handle_word");
    const char **input_ptr = data->input;
    size_t *pos_ptr = data->buf_pos;
    
    // ADD opening quote to buffer
    data->buffer[*pos_ptr] = '"';
    (*pos_ptr)++;
    (*input_ptr)++; // Skip past opening quote in input
    
    // Collect characters until closing quote
    while (**input_ptr && **input_ptr != '"')
    {
        data->buffer[*pos_ptr] = **input_ptr;
        (*pos_ptr)++;
        (*input_ptr)++;
    }
    
    if (**input_ptr == '"')
    {
        // ADD closing quote to buffer
        data->buffer[*pos_ptr] = '"';
        (*pos_ptr)++;
        (*input_ptr)++; // Skip closing quote in input
        *(data->state) = IN_WORD; // Continue building same token
    }
    else
    {
        *(data->state) = IN_WORD; // Continue as word if unclosed
    }
    return (1);
}

int handle_single_quote(t_lexer_data *data)
{
	debug_lexer_step(data, "ENTERING handle_word");
    const char **input_ptr = data->input;
    size_t *pos_ptr = data->buf_pos;
    
    // ADD opening quote to buffer
    data->buffer[*pos_ptr] = '\'';
    (*pos_ptr)++;
    (*input_ptr)++; // Skip past opening quote in input
    
    while (**input_ptr && **input_ptr != '\'')
    {
        data->buffer[*pos_ptr] = **input_ptr;
        (*pos_ptr)++;
        (*input_ptr)++;
    }
    
    if (**input_ptr == '\'')
    {
        // ADD closing quote to buffer
        data->buffer[*pos_ptr] = '\'';
        (*pos_ptr)++;
        (*input_ptr)++; // Skip closing quote in input
        *(data->state) = IN_WORD; // Continue building same token
    }
    else
    {
        *(data->state) = IN_WORD; // Continue as word if unclosed
    }
    return (1);
}