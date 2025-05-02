/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 15:48:08 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *init_command(void)
{
    t_command   *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = malloc(sizeof(char *) * 10);
    if (!cmd->args)
        return (free(cmd), NULL);
    cmd->args[0] = NULL;
    cmd->infiles = malloc(sizeof(char *) * 2);
    if (!cmd->infiles)
        return (free(cmd->args), free(cmd), NULL);
    cmd->infiles[0] = NULL;
    cmd->outfiles = malloc(sizeof(char *) * 2);
    if (!cmd->outfiles)
        return (free(cmd->args), free(cmd->infiles), free(cmd), NULL);
    cmd->outfiles[0] = NULL;
    cmd->cmdpath = NULL;
    cmd->errormsg = NULL;
    cmd->append = 0;
    cmd->heredoc_input = NULL;
    cmd->next = NULL;
    return (cmd);
}

void free_command(t_command *cmd)
{
    size_t  i;

    if (!cmd)
        return ;
    i = 0;
    while (cmd->args[i])
        free(cmd->args[i++]);
    free(cmd->args);
    i = 0;
    while (cmd->infiles[i])
        free(cmd->infiles[i++]);
    free(cmd->infiles);
    i = 0;
    while (cmd->outfiles[i])
        free(cmd->outfiles[i++]);
    free(cmd->outfiles);
    free(cmd->cmdpath);
    free(cmd->errormsg);
    free(cmd->heredoc_input);
    free_command(cmd->next);
    free(cmd);
}

int add_arg(t_command *cmd, char *arg)
{
    size_t  i;
    char    *dup;
    char    **new_args;

    if (!arg || arg[0] == '\0')
        return (1);

    dup = ft_strdup(arg);
    if (!dup)
        return (0);
    i = 0;
    while (cmd->args[i])
        i++;
    if (i >= 10)
    {
        new_args = malloc(sizeof(char *) * (i * 2));
        if (!new_args)
            return (free(dup), 0);
        i = 0;
        while (cmd->args[i])
        {
            new_args[i] = cmd->args[i];
            i++;
        }
        free(cmd->args);
        cmd->args = new_args;
    }
    cmd->args[i] = dup;
    cmd->args[i + 1] = NULL;
    return (1);
}