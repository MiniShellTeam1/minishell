/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncantona <ncantona@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/13 18:41:56 by ncantona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_errorcode(t_master *master)
{
    // t_command *cmd;

    // cmd = master->cmds;
    master->errorcode = 0;
    // while (cmd)
    // {
    //     if (cmd->errormsg)
    //     {
    //         master->errorcode = 1;
    //         break;
    //     }
    //     cmd = cmd->next;
    // }
}

t_master *init_master(void)
{
    t_master *master;
    
    master = malloc(sizeof(t_master));
    if (!master)
        return (NULL);
    master->cmds = NULL;
    master->env = NULL;
    master->errorcode = 0;
    return (master);
}

void free_master(t_master *master)
{
    t_env *tmp;
    
    if (!master)
        return;
    free_command(master->cmds);
    while (master->env)
    {
        tmp = master->env;
        master->env = master->env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    free(master);
}

static void process_command_line(t_master *master, char *line)
{
    t_token_list *tokens;

    if (*line)
        add_history(line);
    
    tokens = lexer(line);
    debug_shell_state(tokens, NULL, NULL, "After Lexing");
    if (tokens)
    {
        master->cmds = parser(tokens, master);
        debug_shell_state(NULL, master->cmds, NULL, "After Parsing");
        
        if (master->cmds)
        {
            handle_heredoc(master->cmds, master);
            set_errorcode(master);
            debug_shell_state(NULL, NULL, master, "Before Executor");
            ft_exec(master);
            free_command(master->cmds);
            master->cmds = NULL;
        }
        free_token_list(tokens);
    }
}

int main(int argc, char *argv[], char **env)
{
    t_master *master;
    char *line;

    (void)argc;
    (void)argv;
    master = init_master();
    if (!master)
        return (1);
    master->env = ft_createenvlist(env);
    setup_signals();
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
        {
            write(1, "exit\n", 5);
            break;
        }
        if (check_signal())
        {
            free(line);
            continue;
        }
        process_command_line(master, line);
        free(line);
    }
    free_master(master);
    return (master->errorcode);
}