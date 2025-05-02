/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 18:46:21 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_builtin(const char *cmd)
{
    const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", 
                              "exit", "cat", NULL};
    int i;

    i = 0;
    if (!cmd)
        return (0);
    
    while (builtins[i])
    {
        if (!ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1))
            return (1);
        i++;
    }
    return (0);
}

static void validate_command(t_command *cmd)
{
    if (!cmd->args[0] || !cmd->args[0][0])
    {
        cmd->cmdpath = NULL;
        cmd->errormsg = NULL;
        return;
    }
    if (is_builtin(cmd->args[0]))
    {
        free(cmd->cmdpath);
        cmd->cmdpath = ft_strdup(cmd->args[0]);
        free(cmd->errormsg);
        cmd->errormsg = NULL;
    }
    else
    {
        free(cmd->cmdpath);
        cmd->cmdpath = NULL;
        free(cmd->errormsg);
        cmd->errormsg = ft_strdup("command not found");
    }
}

static int process_redirect_token(t_command **current, size_t *i, 
                                  t_token_list *tokens)
{
    if (!ft_strncmp(tokens->tokens[*i], "<<", 3))
    {
        (*current)->infiles[0] = ft_strjoin("<<", tokens->tokens[*i + 1]);
        (*i)++;
        return (1);
    }
    else if (!set_redirect(*current, tokens->tokens[*i], tokens->tokens[*i + 1]))
        return (0);
    (*i)++;
    return (1);
}

static int process_pipe_token(t_command **head, t_command **current, int *pipe_flag)
{
    (void)head;
    if (*pipe_flag)
    {
        (*current)->next = init_command();
        if (!(*current)->next)
            return (0);
        *current = (*current)->next;
        *pipe_flag = 0;
        validate_command(*current);
    }
    return (1);
}

t_command *parser(t_token_list *tokens, t_master *master)
{
    t_command   *head;
    t_command   *current;
    size_t      i;
    int         pipe_flag;
    int         result;

    head = init_command();
    if (!head)
        return (NULL);
    current = head;
    i = 0;
    pipe_flag = 0;
    while (i < tokens->count)
    {
        result = process_token(&current, tokens->tokens[i], &pipe_flag, master);
        if (result == 2)
        {
            if (!process_redirect_token(&current, &i, tokens))
                return (free_command(head), NULL);
        }
        else if (!process_pipe_token(&head, &current, &pipe_flag))
            return (free_command(head), NULL);
        i++;
    }
    validate_command(head);
    validate_command(current);
    return (head);
}