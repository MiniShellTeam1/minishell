#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>
#include <stdio.h>

static void handle_heredoc(t_command *cmd)
{
    char    *line;

    if (cmd->redirect_in && !ft_strncmp(cmd->redirect_in, "<<", 2))
    {
        printf("heredoc> ");
        while ((line = readline("")) != NULL)
        {
            if (!ft_strncmp(line, cmd->redirect_in + 2, ft_strlen(cmd->redirect_in + 2)))
                break ;
            free(line);
        }
        free(line);
    }
}

int main(void)
{
    char        *line;
    t_token_list    *tokens;
    t_command       *cmd;

    while ((line = readline("$ ")) != NULL)
    {
        tokens = lexer(line);
        if (tokens)
        {
            cmd = parser(tokens);
            if (cmd)
            {
                handle_heredoc(cmd);
                print_command(cmd);
                free_command(cmd);
            }
            free_token_list(tokens);
        }
        free(line);
    }
    return (0);
}