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
    if (!data || !data->buffer || !data->buf_pos || !data->input || !*(data->input))
        return (0);

    if (**(data->input) == ' ' || **(data->input) == '|' || 
        **(data->input) == '<' || **(data->input) == '>')
    {
        *(data->state) = NORMAL;
        (data->buffer)[*(data->buf_pos)] = '\0';
        
        write(1, "handle_word adding token: ", 26);
        write(1, data->buffer, ft_strlen(data->buffer));
        write(1, "\n", 1);
        
        if (!add_token(data->tokens, data->buffer))
            return (0);
        *(data->buf_pos) = 0;
        return (1);
    }
    if (**(data->input) == '"')
    {
        // Add current word as token if any
        if (*(data->buf_pos) > 0)
        {
            (data->buffer)[*(data->buf_pos)] = '\0';
            write(1, "handle_word adding token: ", 26);
            write(1, data->buffer, ft_strlen(data->buffer));
            write(1, "\n", 1);
            if (!add_token(data->tokens, data->buffer))
                return (0);
            *(data->buf_pos) = 0;
        }
        *(data->state) = IN_DOUBLE_QUOTE;
        (data->buffer)[*(data->buf_pos)] = **(data->input);
        (*(data->buf_pos))++;
        (*(data->input))++;
        return (1);
    }
    if (**(data->input) == '\'')
    {
        if (*(data->buf_pos) > 0)
        {
            (data->buffer)[*(data->buf_pos)] = '\0';
            write(1, "handle_word adding token: ", 26);
            write(1, data->buffer, ft_strlen(data->buffer));
            write(1, "\n", 1);
            if (!add_token(data->tokens, data->buffer))
                return (0);
            *(data->buf_pos) = 0;
        }
        *(data->state) = IN_SINGLE_QUOTE;
        (data->buffer)[*(data->buf_pos)] = **(data->input);
        (*(data->buf_pos))++;
        (*(data->input))++;
        return (1);
    }
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
        
        write(1, "handle_operator adding token: ", 30);
        write(1, data->buffer, ft_strlen(data->buffer));
        write(1, "\n", 1);
        
        if (!add_token(data->tokens, data->buffer))
            return (0);
        *(data->buf_pos) = 0;
    }
    return (1);
}