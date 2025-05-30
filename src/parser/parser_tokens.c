/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/30 16:04:27 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int should_expand_variables(char *token)
{
    int i = 0;
    int in_single_quotes = 0;
    int in_double_quotes = 0;
    int should_expand = 0;
    
     printf("DEBUG should_expand_variables: token='%s'\n", token);
    
    while (token[i])
    {
        if (token[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
             printf("DEBUG: Toggle single quotes at pos %d, now in_single=%d\n", i, in_single_quotes);
        }
        else if (token[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
             printf("DEBUG: Toggle double quotes at pos %d, now in_double=%d\n", i, in_double_quotes);
        }
        else if (token[i] == '$')
        {
            printf("DEBUG: Found $ at pos %d, in_single=%d, in_double=%d\n", i, in_single_quotes, in_double_quotes);
            // Expand if NOT in single quotes
            if (!in_single_quotes)
            {
                should_expand = 1;
                 printf("DEBUG: $ can be expanded (not in single quotes)\n");
            }
            else
            {
                 printf("DEBUG: $ cannot be expanded (in single quotes)\n");
            }
        }
        i++;
    }
    
     printf("DEBUG: Final result: should_expand=%d\n", should_expand);
    return (should_expand);
}

static int process_token_pipe(t_parser_data *data)
{
    if (!ft_strncmp(data->token, "|", 2))
    {
        *(data->pipe_flag) = 1;
        return (1);
    }
    return (0);
}

static int process_token_redirect(t_parser_data *data)
{
    if (!ft_strncmp(data->token, ">", 2) ||
        !ft_strncmp(data->token, ">>", 3) ||
        !ft_strncmp(data->token, "<", 2) ||
        !ft_strncmp(data->token, "<<", 3))
        return (2);
    return (0);
}

static int process_token_word(t_parser_data *data)
{
    char *stripped;

    stripped = strip_quotes(data->token);
    if (!stripped)
        return (0);
    if (stripped[0] != '\0')
    {
        if (!add_arg(*(data->cmd), stripped))
        {
            free(stripped);
            return (0);
        }
    }
    free(stripped);
    return (1);
}

int process_token(t_command **cmd, char *token, int *pipe_flag, t_master *master)
{
    t_parser_data data;
    int result;

    data.cmd = cmd;
    data.token = token;
    data.pipe_flag = pipe_flag;
    data.master = master;

    result = process_token_pipe(&data);
    if (result)
        return (result);

    result = process_token_redirect(&data);
    if (result)
        return (result);

    if (ft_strchr(token, '$') && should_expand_variables(token))
        return (process_token_variable(&data));

    return (process_token_word(&data));
}