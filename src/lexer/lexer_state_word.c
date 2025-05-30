/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 15:30:00 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_word(t_lexer_data *data)
{
    debug_lexer_step(data, "ENTERING handle_word");
    if (!data || !data->buffer || !data->buf_pos || !data->input || !*(data->input))
        return (0);
    
    // End token on whitespace or operators
    if (**(data->input) == ' ' || **(data->input) == '\t' ||
        **(data->input) == '|' || **(data->input) == '<' ||
        **(data->input) == '>')
    {
        *(data->state) = NORMAL;
        (data->buffer)[*(data->buf_pos)] = '\0';
        if (!add_token(data->tokens, data->buffer))
            return (0);
        *(data->buf_pos) = 0;
        return (1);
    }
    
    // Transition to quotes WITHOUT skipping quote character
    if (**(data->input) == '"')
    {
        *(data->state) = IN_DOUBLE_QUOTE;
        // DON'T skip quote here - let handle_double_quote handle it
        return (1);
    }
    
    if (**(data->input) == '\'')
    {
        *(data->state) = IN_SINGLE_QUOTE;
        // DON'T skip quote here - let handle_single_quote handle it
        return (1);
    }
    
    // Add regular character to buffer
    if (*(data->buf_pos) < 1023)
    {
        (data->buffer)[*(data->buf_pos)] = **(data->input);
        (*(data->buf_pos))++;
        (*(data->input))++;
    }
    else
    {
        (*(data->input))++;
    }
    return (1);
}

int handle_operator(t_lexer_data *data)
{
    if (!data || !data->buffer || !data->buf_pos || !data->input || !*(data->input) || !data->state)
        return (0);
    
    if (*(data->buf_pos) == 1 && 
        (((data->buffer)[0] == '>' && **(data->input) == '>') ||
         ((data->buffer)[0] == '<' && **(data->input) == '<')))
    {
        if (*(data->buf_pos) < 1023)
        {
            (data->buffer)[*(data->buf_pos)] = **(data->input);
            (*(data->buf_pos))++;
            (*(data->input))++;
        }
        else
        {
            (*(data->input))++;
        }
    }
    else
    {
        *(data->state) = NORMAL;
        if (*(data->buf_pos) < 1024)
            (data->buffer)[*(data->buf_pos)] = '\0';
        
        if (!add_token(data->tokens, data->buffer))
            return (0);
        *(data->buf_pos) = 0;
    }
    return (1);
}