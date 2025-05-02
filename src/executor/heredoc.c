/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 18:47:08 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_quoted_delimiter(char *delimiter)
{
    size_t len = ft_strlen(delimiter);
    return (len >= 2 && ((delimiter[0] == '"' && delimiter[len - 1] == '"') ||
                         (delimiter[0] == '\'' && delimiter[len - 1] == '\'')));
}

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
    if (!input || ft_strncmp(input, "<<", 2) != 0)
        return (NULL);
    
    return (input + 2);
}

void handle_heredoc(t_command *cmd, t_master *master)
{
    char    *line;
    char    *expanded_line;
    char    *heredoc_content;
    char    *delimiter;
    char    *clean_delimiter;
    size_t  delim_len;
    int     expand_vars;
    t_token_list *new_tokens;
    size_t  i;

    if (!cmd->infiles || !cmd->infiles[0] || 
        ft_strncmp(cmd->infiles[0], "<<", 2) != 0)
        return;
    
    delimiter = get_heredoc_delimiter(cmd->infiles[0]);
    if (!delimiter)
        return;
    
    // Strip quotes from delimiter for comparison
    clean_delimiter = strip_quotes(delimiter);
    if (!clean_delimiter)
        return;
    
    expand_vars = !is_quoted_delimiter(delimiter);
    delim_len = ft_strlen(clean_delimiter);
    heredoc_content = NULL;
    
    while (1)
    {
        write(1, "heredoc> ", 9);
        line = readline("");
        
        if (!line)
            break;
        
        if (!ft_strncmp(line, clean_delimiter, delim_len) && 
            line[delim_len] == '\0')
        {
            free(line);
            break;
        }
        
        if (expand_vars)
        {
            // Lex the input line to handle multiple variables
            new_tokens = lexer(line);
            if (!new_tokens)
            {
                free(line);
                free(clean_delimiter);
                if (heredoc_content)
                    free(heredoc_content);
                return;
            }
            
            expanded_line = ft_strdup("");
            if (!expanded_line)
            {
                free_token_list(new_tokens);
                free(line);
                free(clean_delimiter);
                if (heredoc_content)
                    free(heredoc_content);
                return;
            }
            
            i = 0;
            while (i < new_tokens->count)
            {
                char *temp = expand_variable(new_tokens->tokens[i], master);
                if (!temp)
                {
                    free(expanded_line);
                    free_token_list(new_tokens);
                    free(line);
                    free(clean_delimiter);
                    if (heredoc_content)
                        free(heredoc_content);
                    return;
                }
                char *new_expanded = ft_strjoin(expanded_line, temp);
                free(expanded_line);
                free(temp);
                if (!new_expanded)
                {
                    free_token_list(new_tokens);
                    free(line);
                    free(clean_delimiter);
                    if (heredoc_content)
                        free(heredoc_content);
                    return;
                }
                expanded_line = new_expanded;
                i++;
            }
            
            free_token_list(new_tokens);
            free(line);
            line = expanded_line;
        }
        
        char *new_content = concat_heredoc_line(heredoc_content, line);
        if (heredoc_content)
            free(heredoc_content);
        heredoc_content = new_content;
        
        free(line);
    }
    
    free(clean_delimiter);
    cmd->heredoc_input = heredoc_content;
}