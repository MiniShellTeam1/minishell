/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 13:18:18 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process_char(t_lexer_data *data)
{
    if (*(data->state) == NORMAL)
        return (handle_normal(data));
    if (*(data->state) == IN_SINGLE_QUOTE)
        return (handle_single_quote(data));
    if (*(data->state) == IN_DOUBLE_QUOTE)
        return (handle_double_quote(data));
    if (*(data->state) == IN_WORD)
        return (handle_word(data));
    return (handle_operator(data));
}

t_token_list *lexer(char const *input)
{
    t_state         state;
    char            *buffer;
    size_t          buf_pos;
    t_token_list    *tokens;
    t_lexer_data    data;

    if (!input)
        return (NULL);
    
    state = NORMAL;
    buffer = malloc(1024);
    if (!buffer)
        return (NULL);
    buf_pos = 0;
    tokens = init_token_list();
    if (!tokens)
    {
        free(buffer);
        return (NULL);
    }
    data.state = &state;
    data.input = &input;
    data.tokens = tokens;
    data.buffer = buffer;
    data.buf_pos = &buf_pos;

    while (*input)
    {
        if (!process_char(&data))
        {
            free(buffer);
            free_token_list(tokens);
            return (NULL);
        }
    }
    if (buf_pos > 0 && state == IN_WORD)
    {

        buffer[buf_pos] = '\0';
        if (!add_token(tokens, buffer))
        {
            free(buffer);
            free_token_list(tokens);
            return (NULL);
        }
    }
    
    free(buffer);
    return (tokens);
}