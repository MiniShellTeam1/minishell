/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 11:11:34 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list *init_token_list(void)
{
    t_token_list    *list;

    list = malloc(sizeof(t_token_list));
    if (!list)
        return (NULL);
    list->tokens = malloc(sizeof(char *) * 10);
    if (!list->tokens)
        return (free(list), NULL);
    list->count = 0;
    list->capacity = 10;
    return (list);
}

int add_token(t_token_list *tokens, char *buffer)
{
    char    **new_tokens;
    char    *token;
    size_t  i;

    token = ft_strdup(buffer);
    if (!token)
        return (0);
    if (tokens->count >= tokens->capacity)
    {
        tokens->capacity *= 2;
        new_tokens = malloc(sizeof(char *) * tokens->capacity);
        if (!new_tokens)
            return (free(token), 0);
        i = 0;
        while (i < tokens->count)
        {
            new_tokens[i] = tokens->tokens[i];
            i++;
        }
        free(tokens->tokens);
        tokens->tokens = new_tokens;
    }
    tokens->tokens[tokens->count] = token;
    tokens->count++;
    return (1);
}

void free_token_list(t_token_list *tokens)
{
    size_t  i;

    i = 0;
    while (i < tokens->count)
    {
        free(tokens->tokens[i]);
        i++;
    }
    free(tokens->tokens);
    free(tokens);
}