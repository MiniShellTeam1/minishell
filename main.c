#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>
#include <stdio.h>

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
                free_command(cmd);
            free_token_list(tokens);
        }
        free(line);
    }
    return (0);
}