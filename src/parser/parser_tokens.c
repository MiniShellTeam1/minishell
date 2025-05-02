/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 17:43:13 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    if (ft_strchr(token, '$') && (token[0] != '\'' || !ft_strchr(token + 1, '\'')))
        return (process_token_variable(&data));

    return (process_token_word(&data));
}