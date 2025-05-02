/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 13:18:59 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int append_to_array(char ***array, char *new_item)
{
    size_t  count;
    char    **new_array;
    size_t  i;

    count = 0;
    while ((*array)[count])
        count++;
    new_array = malloc(sizeof(char *) * (count + 2));
    if (!new_array)
        return (0);
    i = 0;
    while (i < count)
    {
        new_array[i] = (*array)[i];
        i++;
    }
    new_array[i] = ft_strdup(new_item);
    if (!new_array[i])
    {
        while (i > 0)
            free(new_array[--i]);
        free(new_array);
        return (0);
    }
    new_array[i + 1] = NULL;
    free(*array);
    *array = new_array;
    return (1);
}

static int set_output_redirect(t_command *cmd, char *token, char *stripped_token)
{
    if (!ft_strncmp(token, ">", 2))
    {
        cmd->append = 0;
        if (!append_to_array(&cmd->outfiles, stripped_token))
            return (0);
    }
    else if (!ft_strncmp(token, ">>", 3))
    {
        cmd->append = 1;
        if (!append_to_array(&cmd->outfiles, stripped_token))
            return (0);
    }
    return (1);
}

static int set_input_redirect(t_command *cmd, char *token, char *stripped_token)
{
    if (!ft_strncmp(token, "<", 2))
    {
        if (!append_to_array(&cmd->infiles, stripped_token))
            return (0);
    }
    else if (!ft_strncmp(token, "<<", 3))
    {
        char *heredoc_token = ft_strjoin("<<", stripped_token);
        if (!heredoc_token)
            return (0);
        
        if (!append_to_array(&cmd->infiles, heredoc_token))
        {
            free(heredoc_token);
            return (0);
        }
        
        free(heredoc_token);
    }
    return (1);
}

int set_redirect(t_command *cmd, char *token, char *next_token)
{
    char *stripped_token;
    int result;
    
    if (!next_token)
        return (0);
    
    stripped_token = strip_quotes(next_token);
    if (!stripped_token)
        return (0);
    
    if (token[0] == '>')
        result = set_output_redirect(cmd, token, stripped_token);
    else
        result = set_input_redirect(cmd, token, stripped_token);
    
    free(stripped_token);
    return (result);
}