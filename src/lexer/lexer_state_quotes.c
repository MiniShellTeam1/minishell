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
    const char **input_ptr = data->input;
    size_t *pos_ptr = data->buf_pos;
    data->buffer[*pos_ptr] = **input_ptr;
    (*pos_ptr)++;
    (*input_ptr)++;
    while (**input_ptr && **input_ptr != '"')
    {
        data->buffer[*pos_ptr] = **input_ptr;
        (*pos_ptr)++;
        (*input_ptr)++;
    }
    
    if (**input_ptr == '"')
    {
        data->buffer[*pos_ptr] = **input_ptr;
        (*pos_ptr)++;
        (*input_ptr)++;
        if (!**input_ptr || **input_ptr == ' ' || **input_ptr == '|' || 
            **input_ptr == '<' || **input_ptr == '>')
        {
            *(data->state) = NORMAL;
            data->buffer[*pos_ptr] = '\0';
            
            write(1, "handle_double_quote adding token: ", 34);
            write(1, data->buffer, ft_strlen(data->buffer));
            write(1, "\n", 1);
            
            if (!add_token(data->tokens, data->buffer))
                return (0);
            *pos_ptr = 0;
        }
        else
        {
            *(data->state) = IN_WORD;
        }
    }
    else
    {
        *(data->state) = NORMAL;
        data->buffer[*pos_ptr] = '\0';
        
        write(1, "handle_double_quote adding token (unclosed): ", 45);
        write(1, data->buffer, ft_strlen(data->buffer));
        write(1, "\n", 1);
        
        if (!add_token(data->tokens, data->buffer))
            return (0);
        *pos_ptr = 0;
    }
    
    return (1);
}

int handle_single_quote(t_lexer_data *data)
{
    const char **input_ptr = data->input;
    size_t *pos_ptr = data->buf_pos;
    data->buffer[*pos_ptr] = **input_ptr;
    (*pos_ptr)++;
    (*input_ptr)++;
    while (**input_ptr && **input_ptr != '\'')
    {
        data->buffer[*pos_ptr] = **input_ptr;
        (*pos_ptr)++;
        (*input_ptr)++;
    }
    
    if (**input_ptr == '\'')
    {
        data->buffer[*pos_ptr] = **input_ptr;
        (*pos_ptr)++;
        (*input_ptr)++;
        if (!**input_ptr || **input_ptr == ' ' || **input_ptr == '|' || 
            **input_ptr == '<' || **input_ptr == '>')
        {
            *(data->state) = NORMAL;
            data->buffer[*pos_ptr] = '\0';
            
            write(1, "handle_single_quote adding token: ", 34);
            write(1, data->buffer, ft_strlen(data->buffer));
            write(1, "\n", 1);
            
            if (!add_token(data->tokens, data->buffer))
                return (0);
            *pos_ptr = 0;
        }
        else
        {
            *(data->state) = IN_WORD;
        }
    }
    else
    {
        *(data->state) = NORMAL;
        data->buffer[*pos_ptr] = '\0';
        
        write(1, "handle_single_quote adding token (unclosed): ", 45);
        write(1, data->buffer, ft_strlen(data->buffer));
        write(1, "\n", 1);
        
        if (!add_token(data->tokens, data->buffer))
            return (0);
        *pos_ptr = 0;
    }
    
    return (1);
}