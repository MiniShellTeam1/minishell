/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:55 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/23 10:59:33 by mhuthmay         ###   ########.fr       */
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

int process_token(t_command **cmd, char *token, int *pipe_flag, t_master *master)
{
    char *expanded, *prefix, *joined;
    t_token_list *new_tokens;
    size_t i, prefix_len;

    if (!ft_strncmp(token, "|", 2))
    {
        *pipe_flag = 1;
        return (1);
    }
    if (!ft_strncmp(token, ">", 2) || !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<", 2) || !ft_strncmp(token, "<<", 3))
        return (2);
    
    // check if token contains a variable
    if (strchr(token, '$'))
    {
        // extract prefix (before $) and variable
        prefix_len = 0;
        while (token[prefix_len] && token[prefix_len] != '$')
            prefix_len++;
        prefix = ft_strndup(token, prefix_len);
        expanded = expand_variable(token + prefix_len, master);
        if (!prefix || !expanded)
        {
            free(prefix);
            free(expanded);
            return (0);
        }
        // join tuff before $ and expanded value
        joined = ft_strjoin(prefix, expanded);
        free(prefix);
        free(expanded);
        if (!joined)
            return (0);
        // Re-lex the joined string
        new_tokens = lexer(joined);
        free(joined);
        if (!new_tokens)
            return (0);
        // Add tokens to cmd->args
        i = 0;
        while (i < new_tokens->count)
        {
            if (!add_arg(*cmd, strip_quotes(new_tokens->tokens[i])))
            {
                free_token_list(new_tokens);
                return (0);
            }
            i++;
        }
        free_token_list(new_tokens);
    }
    else
    {
        // Non-variable token: add directly
        if (!add_arg(*cmd, strip_quotes(ft_strdup(token))))
            return (0);
    }
    return (1);
}

static int is_builtin(const char *cmd)
{
    const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", "cat", NULL};
    int i = 0;

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
        cmd->cmdpath = ft_strdup(cmd->args[0]); // delete this
        cmd->errormsg = NULL; // delete error message
    }
    else
    {
        cmd->cmdpath = NULL;
        cmd->errormsg = ft_strdup("command not found");
    }
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
            if (!ft_strncmp(tokens->tokens[i], "<<", 3))
                current->infiles[0] = ft_strjoin("<<", tokens->tokens[i + 1]);
            else if (!set_redirect(current, tokens->tokens[i], tokens->tokens[i + 1]))
                return (free_command(head), NULL);
            i++;
        }
        else if (pipe_flag)
        {
            current->next = init_command();
            if (!current->next)
                return (free_command(head), NULL);
            current = current->next;
            pipe_flag = 0;
            validate_command(current);
        }
        else if (result == 1)
        {
            // Pipe token, already handled
        }
        else if (result == 0)
        {
            // Error in process_token
            return (free_command(head), NULL);
        }
        else
        {
            // Token was added by process_token
        }
        i++;
    }
    validate_command(head);
    validate_command(current);
    return (head);
}
