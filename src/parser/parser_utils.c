/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:43 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/23 16:51:56 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *strip_quotes(char *token)
{
    size_t len;
    char *result;
    size_t i;

    if (!token)
        return (NULL);
    len = ft_strlen(token);
    if (len < 1)
        return (ft_strdup(""));
    if (len == 2 && token[0] == '"' && token[1] == '"')
        return (ft_strdup(""));
    if (token[0] != '"' && token[0] != '\'')
        return (ft_strdup(token));
    result = malloc(len);
    if (!result)
        return (NULL);
    i = 0;
    while (i < len - 1 && token[i + 1])
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

char *expand_variable(char *token, t_master *master)
{
    t_env *env;

    if (!token || token[0] != '$')
        return (ft_strdup(token));
    if (!ft_strncmp(token, "$?", 3))
        return (ft_itoa(master->errorcode));
    env = master->env;
    while (env)
    {
        if (!ft_strcmp(token + 1, env->key))
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (ft_strdup(""));
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