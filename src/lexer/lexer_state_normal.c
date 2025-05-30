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
    if (**(data->input) == ' ')
    {
        (*(data->input))++;
        return (1);
    }
    
    if (**(data->input) == '"')
    {
        *(data->state) = IN_DOUBLE_QUOTE;
        // DON'T skip quote here - let handle_double_quote do it
        return (1);
    }
    
    if (**(data->input) == '\'')
    {
        *(data->state) = IN_SINGLE_QUOTE;
        // DON'T skip quote here - let handle_single_quote do it
        return (1);
    }
    
    if (**(data->input) == '|' || **(data->input) == '<' || 
        **(data->input) == '>')
    {
        *(data->state) = IN_OPERATOR;
        (data->buffer)[*(data->buf_pos)] = **(data->input);
        (*(data->buf_pos))++;
        (*(data->input))++;
        return (1);
    }
    
    // Start unquoted word
    *(data->state) = IN_WORD;
    (data->buffer)[*(data->buf_pos)] = **(data->input);
    (*(data->buf_pos))++;
    (*(data->input))++;
    return (1);
}