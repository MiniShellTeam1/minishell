/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 13:19:36 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process_token_normal(t_parser_data *data)
{
    char *stripped;
    
    stripped = strip_quotes(data->token);
    if (!stripped)
        return (0);
    
    if (!add_arg(*(data->cmd), stripped))
    {
        free(stripped);
        return (0);
    }
    
    free(stripped);
    return (1);
}

static char *get_prefix(char *token, size_t *prefix_len)
{
    *prefix_len = 0;
    while (token[*prefix_len] && token[*prefix_len] != '$')
        (*prefix_len)++;
    
    return (ft_strndup(token, *prefix_len));
}

static size_t get_var_end(char *token, size_t start)
{
    size_t i;
    
    i = start;
    while (token[i] && (
           (token[i] >= 'A' && token[i] <= 'Z') || 
           (token[i] >= 'a' && token[i] <= 'z') || 
           (token[i] >= '0' && token[i] <= '9') || 
           token[i] == '_' || token[i] == '$' || 
           token[i] == '?'))
        i++;
    
    return (i);
}

int process_token_variable(t_parser_data *data)
{
    char *expanded, *prefix, *suffix, *joined, *stripped;
    t_token_list *new_tokens;
    size_t i, prefix_len, suffix_start;
    
    prefix = get_prefix(data->token, &prefix_len);
    
    suffix_start = get_var_end(data->token, prefix_len);
    
    expanded = expand_variable(data->token + prefix_len, data->master);
    
    suffix = ft_strdup(data->token + suffix_start);
    
    if (!prefix || !expanded || !suffix)
    {
        free(prefix);
        free(expanded);
        free(suffix);
        return (0);
    }
    
    joined = ft_strjoin3(prefix, expanded, suffix);
    free(prefix);
    free(expanded);
    free(suffix);
    
    if (!joined)
        return (0);
    
    new_tokens = lexer(joined);
    free(joined);
    
    if (!new_tokens)
        return (0);
    
    i = 0;
    while (i < new_tokens->count)
    {
        stripped = strip_quotes(new_tokens->tokens[i]);
        if (!stripped)
        {
            free_token_list(new_tokens);
            return (0);
        }
        
        if (!add_arg(*(data->cmd), stripped))
        {
            free(stripped);
            free_token_list(new_tokens);
            return (0);
        }
        
        free(stripped);
        i++;
    }
    
    free_token_list(new_tokens);
    return (1);
}