/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_normal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 15:30:00 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_normal(t_lexer_data *data)
{
    if (!data || !data->state || !data->input || !*(data->input) || 
        !data->buffer || !data->buf_pos)
        return (0);
    if (**(data->input) == ' ')
    {
        (*(data->input))++;
        return (1);
    }
    if (**(data->input) == '"')
    {
        *(data->state) = IN_DOUBLE_QUOTE;
        if (*(data->buf_pos) < 1023)
        {
            (data->buffer)[*(data->buf_pos)] = **(data->input);
            (*(data->buf_pos))++;
        }
        (*(data->input))++;
        return (1);
    }
    if (**(data->input) == '\'')
    {
        *(data->state) = IN_SINGLE_QUOTE;
        if (*(data->buf_pos) < 1023)
        {
            (data->buffer)[*(data->buf_pos)] = **(data->input);
            (*(data->buf_pos))++;
        }
        (*(data->input))++;
        return (1);
    }
    if (**(data->input) == '|' || **(data->input) == '<' || 
        **(data->input) == '>')
    {
        *(data->state) = IN_OPERATOR;
        if (*(data->buf_pos) < 1023)
        {
            (data->buffer)[*(data->buf_pos)] = **(data->input);
            (*(data->buf_pos))++;
        }
        (*(data->input))++;
        return (1);
    }
    
    *(data->state) = IN_WORD;
    if (*(data->buf_pos) < 1023)
    {
        (data->buffer)[*(data->buf_pos)] = **(data->input);
        (*(data->buf_pos))++;
    }
    (*(data->input))++;
    
    return (1);
}