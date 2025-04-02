#include "libft.h"
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static void handle_heredoc(s_command *cmd)
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
            if (!line) // Handle Ctrl+D (EOF)
                break;
            len = ft_strlen(line);
            if (len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0'; // Strip trailing newline
            if (!ft_strncmp(line, cmd->infiles[0] + 2, ft_strlen(cmd->infiles[0] + 2)))
            {
                free(line);
                break ;
            }
            // Append the line to heredoc_content
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
        cmd->heredoc_input = heredoc_content; // Store in s_command
    }
}

static void print_command(s_command *cmd)
{
    size_t  i;

    while (cmd)
    {
        i = 0;
        write(1, "Command: ", 9);
        while (cmd->cmdargs[i])
        {
            write(1, cmd->cmdargs[i], ft_strlen(cmd->cmdargs[i]));
            write(1, " ", 1);
            i++;
        }
        i = 0;
        while (cmd->infiles[i])
        {
            write(1, "< ", 2);
            write(1, cmd->infiles[i], ft_strlen(cmd->infiles[i]));
            write(1, " ", 1);
            i++;
        }
        i = 0;
        while (cmd->outfiles[i])
        {
            write(1, cmd->append ? ">> " : "> ", 2);
            write(1, cmd->outfiles[i], ft_strlen(cmd->outfiles[i]));
            write(1, " ", 1);
            i++;
        }
        if (cmd->heredoc_input)
        {
            write(1, "Heredoc input:\n", 15);
            write(1, cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
        }
        if (cmd->cmdpath)
        {
            write(1, "Cmdpath: ", 9);
            write(1, cmd->cmdpath, ft_strlen(cmd->cmdpath));
            write(1, " ", 1);
        }
        if (cmd->errormsg)
        {
            write(1, "Error: ", 7);
            write(1, cmd->errormsg, ft_strlen(cmd->errormsg));
            write(1, " ", 1);
        }
        if (cmd->next)
            write(1, "| ", 2);
        write(1, "\n", 1);
        cmd = cmd->next;
    }
}

int main(void)
{
    char        *line;
    t_token_list    *tokens;
    s_command       *cmd;

    while ((line = readline("$ ")) != NULL)
    {
        if (*line)
            add_history(line);
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