/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:23:12 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/23 16:38:40 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include "minishell.h"


// Enable/disable debug output (1 = on, 0 = off)
#define DEBUG 1

void print_tokens(t_token_list *tokens)
{
    size_t i;

    if (!DEBUG)
        return;
    if (!tokens)
    {
        printf("Tokens: NULL\n");
        return;
        }
        printf("Tokens:\n");
        for (i = 0; i < tokens->count; i++)
        {
            printf("  [%zu]: \"", i);
            for (size_t j = 0; tokens->tokens[i][j]; j++)
            {
                if (tokens->tokens[i][j] == '"')
                    printf("\\\"");
                else
                    printf("%c", tokens->tokens[i][j]);
            }
            printf("\"\n");
        }
    }

void print_parsed_commands(t_command *cmd)
{
    t_command *current;
    size_t i;

    if (!DEBUG)
        return;
    if (!cmd)
    {
        printf("Parsed Commands: NULL\n");
        return;
    }
    printf("Parsed Commands:\n");
    current = cmd;
    while (current)
    {
        if (current->args)
        {
            printf("  Command: %s\n", current->args[0]);
            printf("    Arguments:\n");
            i = 1;
            while (current->args[i])
            {
                printf("      - %s\n", current->args[i]);
                i++;
            }
        }
        if (current->infiles)
        {
            printf("    Input Redirects:\n");
            i = 0;
            while (current->infiles[i])
            {
                printf("      - %s\n", current->infiles[i]);
                i++;
            }
        }
        if (current->outfiles)
        {
            printf("    Output Redirects:\n");
            i = 0;
            while (current->outfiles[i])
            {
                printf("      - %s (append: %d)\n", current->outfiles[i], current->append);
                i++;
            }
        }
        if (current->heredoc_input)
            printf("    Heredoc Input: %s\n", current->heredoc_input);
        if (current->cmdpath)
            printf("    Cmdpath: %s\n", current->cmdpath);
        if (current->errormsg)
            printf("    Error: %s\n", current->errormsg);
        current = current->next;
    }
}

void print_master(t_master *master)
{
    if (!DEBUG)
        return;
    if (!master)
    {
        printf("t_master: NULL\n");
        return;
    }
    printf("t_master:\n");
    printf("  cmds:\n");
    print_parsed_commands(master->cmds);
    printf("  env: %s\n", master->env ? "[present]" : "[null]");
    printf("  errorcode: %d\n", master->errorcode);
}

void debug_shell_state(t_token_list *tokens, t_command *cmd, t_master *master, const char *stage)
{
    if (!DEBUG)
        return;
    printf("\n=== Debug: %s ===\n", stage);
    if (tokens)
        print_tokens(tokens);
    if (cmd)
        print_parsed_commands(cmd);
    if (master)
        print_master(master);
    printf("====================\n");
}