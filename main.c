/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:23:07 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 13:23:08 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"
#include "minishell.h"
#include "lexing/lexer.h"
#include "parsing/parser.h"
#include "debug.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static void handle_heredoc(t_command *cmd)
{
    char    *line;
    char    *temp;
    char    *heredoc_content;
    size_t  len;

    if (cmd->infiles && cmd->infiles[0] && !ft_strncmp(cmd->infiles[0], "<<", 2))
    {
        heredoc_content = NULL;
        while (1)
        {
            write(1, "heredoc> ", 9);
            line = readline("");
            if (!line)
                break;
            len = ft_strlen(line);
            if (len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';
            if (!ft_strncmp(line, cmd->infiles[0] + 2, ft_strlen(cmd->infiles[0] + 2)))
            {
                free(line);
                break;
            }
            if (!heredoc_content)
            {
                heredoc_content = ft_strjoin(line, "\n");
            }
            else
            {
                temp = ft_strjoin(heredoc_content, line);
                free(heredoc_content);
                heredoc_content = ft_strjoin(temp, "\n");
                free(temp);
            }
            free(line);
        }
        cmd->heredoc_input = heredoc_content;
    }
}

static void set_errorcode(t_master *master)
{
    t_command *cmd = master->cmds;

    master->errorcode = 0;
    while (cmd)
    {
        if (cmd->errormsg)
        {
            master->errorcode = 1;
            break;
        }
        cmd = cmd->next;
    }
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
    if (!master)
        return;
    free_command(master->cmds);
    free(master);
}

int main(void)
{
    char        *line;
    t_token_list    *tokens;
    t_master        *master;

    while ((line = readline("$ ")) != NULL)
    {
        if (*line)
            add_history(line);
        tokens = lexer(line);
        debug_shell_state(tokens, NULL, NULL, "After Lexing");
        if (tokens)
        {
            master = init_master();
            if (master)
            {
                master->cmds = parser(tokens);
                debug_shell_state(NULL, master->cmds, NULL, "After Parsing");
                if (master->cmds)
                {
                    handle_heredoc(master->cmds);
                    set_errorcode(master);
                    debug_shell_state(NULL, NULL, master, "Before Executor");
                }
                free_master(master);
            }
            free_token_list(tokens);
        }
        free(line);
    }
    return (0);
}
