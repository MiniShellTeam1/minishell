/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 11:15:56 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *concat_heredoc_line(char *current, char *new_line)
{
    char *temp;
    char *result;

    if (!current)
        return (ft_strjoin(new_line, "\n"));
    
    temp = ft_strjoin(current, new_line);
    if (!temp)
        return (NULL);
    
    result = ft_strjoin(temp, "\n");
    free(temp);
    
    return (result);
}

static char *get_heredoc_delimiter(char *input)
{
    if (!input || !ft_strncmp(input, "<<", 2) == 0)
        return (NULL);
    
    return (input + 2);
}

void handle_heredoc(t_command *cmd)
{
    char    *line;
    char    *heredoc_content;
    char    *delimiter;
    size_t  delim_len;

    if (!cmd->infiles || !cmd->infiles[0] || 
        ft_strncmp(cmd->infiles[0], "<<", 2) != 0)
        return;
    
    delimiter = get_heredoc_delimiter(cmd->infiles[0]);
    if (!delimiter)
        return;
    
    delim_len = ft_strlen(delimiter);
    heredoc_content = NULL;
    
    while (1)
    {
        write(1, "heredoc> ", 9);
        line = readline("");
        
        if (!line)
            break;
        
        if (!ft_strncmp(line, delimiter, delim_len) && 
            line[delim_len] == '\0')
        {
            free(line);
            break;
        }
        
        char *new_content = concat_heredoc_line(heredoc_content, line);
        if (heredoc_content)
            free(heredoc_content);
        heredoc_content = new_content;
        
        free(line);
    }
    
    cmd->heredoc_input = heredoc_content;
}