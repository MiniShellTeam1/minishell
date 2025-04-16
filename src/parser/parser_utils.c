/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:43 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 18:44:07 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *strip_quotes(char *token)
{
    size_t  len;
    char    *result;
    size_t  i;

    len = ft_strlen(token);
    if (len < 2 || (token[0] != '"' && token[0] != '\'') || (token[len - 1] != token[0]))
        return (ft_strdup(token));
    result = malloc(len - 1);
    if (!result)
        return (NULL);
    i = 0;
    while (i < len - 2)
    {
        result[i] = token[i + 1];
        i++;
    }
    result[i] = '\0';
    return (result);
}

int is_variable(char *token)
{
    if (!token || token[0] != '$')
        return (0);
    if (token[1] == '?' || (token[1] >= 'A' && token[1] <= 'Z'))
        return (1);
    return (0);
}

char *expand_variable(char *token)
{
    if (!token || token[0] != '$')
        return (ft_strdup(token));
    if (!ft_strncmp(token, "$?", 3))
        return (ft_strdup("0"));
    return (ft_strdup(token));
}

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

int set_redirect(t_command *cmd, char *token, char *next_token)
{
    if (!ft_strncmp(token, ">", 2) || !ft_strncmp(token, ">>", 3))
    {
        cmd->append = (!ft_strncmp(token, ">>", 3));
        return (append_to_array(&cmd->outfiles, next_token));
    }
    if (!ft_strncmp(token, "<", 2))
    {
        return (append_to_array(&cmd->infiles, next_token));
    }
    return (0);
}