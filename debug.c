#include "debug.h"
#include "libft.h"

// Enable debug output (set to 0 to disable)
#define DEBUG 1

static void print_border(int width, char top_left, char top_right, char horizontal)
{
    int i;

    write(1, &top_left, 1);
    for (i = 0; i < width; i++)
        write(1, &horizontal, 1);
    write(1, &top_right, 1);
    write(1, "\n", 1);
}

void debug_print_tokens(t_token_list *tokens)
{
    size_t i;
    int width = 50;
    size_t token_len = 0;

    if (!DEBUG)
        return ;
    print_border(width, '+', '+', '-');
    write(1, "| After Lexing\n", 16);
    write(1, "| Tokens: [", 11);
    for (i = 0; i < tokens->count; i++)
    {
        write(1, tokens->tokens[i], ft_strlen(tokens->tokens[i]));
        token_len += ft_strlen(tokens->tokens[i]);
        if (i < tokens->count - 1)
        {
            write(1, ", ", 2);
            token_len += 2;
        }
    }
    write(1, "]", 1);
    token_len += 1; // For the closing bracket
    for (i = 0; i < width - 10 - token_len; i++)
        write(1, " ", 1);
    write(1, "|\n", 2);
    print_border(width, '+', '+', '-');
}

void debug_print_command(t_command *cmd)
{
    size_t i;
    int width = 50;
    size_t cmd_len;

    if (!DEBUG)
        return ;
    print_border(width, '+', '+', '-');
    write(1, "| After Parsing\n", 17);
    while (cmd)
    {
        cmd_len = 0;
        write(1, "| Command: ", 11);
        i = 0;
        while (cmd->args[i])
        {
            write(1, cmd->args[i], ft_strlen(cmd->args[i]));
            cmd_len += ft_strlen(cmd->args[i]);
            write(1, " ", 1);
            cmd_len += 1;
            i++;
        }
        i = 0;
        while (cmd->infiles[i])
        {
            write(1, "< ", 2);
            write(1, cmd->infiles[i], ft_strlen(cmd->infiles[i]));
            cmd_len += 2 + ft_strlen(cmd->infiles[i]);
            write(1, " ", 1);
            cmd_len += 1;
            i++;
        }
        i = 0;
        while (cmd->outfiles[i])
        {
            write(1, cmd->append ? ">> " : "> ", 2);
            write(1, cmd->outfiles[i], ft_strlen(cmd->outfiles[i]));
            cmd_len += 2 + ft_strlen(cmd->outfiles[i]);
            write(1, " ", 1);
            cmd_len += 1;
            i++;
        }
        if (cmd->heredoc_input)
        {
            write(1, "Heredoc input:\n", 15);
            write(1, cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
            cmd_len += ft_strlen(cmd->heredoc_input);
        }
        if (cmd->cmdpath)
        {
            write(1, "Cmdpath: ", 9);
            write(1, cmd->cmdpath, ft_strlen(cmd->cmdpath));
            cmd_len += 9 + ft_strlen(cmd->cmdpath);
            write(1, " ", 1);
            cmd_len += 1;
        }
        if (cmd->errormsg)
        {
            write(1, "Error: ", 7);
            write(1, cmd->errormsg, ft_strlen(cmd->errormsg));
            cmd_len += 7 + ft_strlen(cmd->errormsg);
            write(1, " ", 1);
            cmd_len += 1;
        }
        if (cmd->next)
        {
            write(1, "| ", 2);
            cmd_len += 2;
        }
        for (i = 0; i < width - 11 - cmd_len; i++)
            write(1, " ", 1);
        write(1, "|\n", 2);
        cmd = cmd->next;
    }
    print_border(width, '+', '+', '-');
}

void debug_print_master(t_master *master)
{
    char *errorcode_str;
    int width = 50;
    size_t env_len;
    size_t err_len;
    long unsigned int i;

    if (!DEBUG)
        return ;
    print_border(width, '+', '+', '-');
    write(1, "| Before Executor\n", 19);
    write(1, "| t_master:\n", 13);
    write(1, "|   cmds:\n", 11);
    t_command *cmd = master->cmds;
    while (cmd)
    {
        size_t cmd_len = 0;
        write(1, "|     Command: ", 15);
        size_t i = 0;
        while (cmd->args[i])
        {
            write(1, cmd->args[i], ft_strlen(cmd->args[i]));
            cmd_len += ft_strlen(cmd->args[i]);
            write(1, " ", 1);
            cmd_len += 1;
            i++;
        }
        i = 0;
        while (cmd->infiles[i])
        {
            write(1, "< ", 2);
            write(1, cmd->infiles[i], ft_strlen(cmd->infiles[i]));
            cmd_len += 2 + ft_strlen(cmd->infiles[i]);
            write(1, " ", 1);
            cmd_len += 1;
            i++;
        }
        i = 0;
        while (cmd->outfiles[i])
        {
            write(1, cmd->append ? ">> " : "> ", 2);
            write(1, cmd->outfiles[i], ft_strlen(cmd->outfiles[i]));
            cmd_len += 2 + ft_strlen(cmd->outfiles[i]);
            write(1, " ", 1);
            cmd_len += 1;
            i++;
        }
        if (cmd->heredoc_input)
        {
            write(1, "Heredoc input:\n", 15);
            write(1, cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
            cmd_len += ft_strlen(cmd->heredoc_input);
        }
        if (cmd->cmdpath)
        {
            write(1, "Cmdpath: ", 9);
            write(1, cmd->cmdpath, ft_strlen(cmd->cmdpath));
            cmd_len += 9 + ft_strlen(cmd->cmdpath);
            write(1, " ", 1);
            cmd_len += 1;
        }
        if (cmd->errormsg)
        {
            write(1, "Error: ", 7);
            write(1, cmd->errormsg, ft_strlen(cmd->errormsg));
            cmd_len += 7 + ft_strlen(cmd->errormsg);
            write(1, " ", 1);
            cmd_len += 1;
        }
        if (cmd->next)
        {
            write(1, "| ", 2);
            cmd_len += 2;
        }
        for (i = 0; i < (size_t)(width - 15 - cmd_len); i++)
            write(1, " ", 1);
        write(1, "|\n", 2);
        cmd = cmd->next;
    }
    write(1, "|   env: ", 8);
    if (master->env)
        write(1, "[present]", 9);
    else
        write(1, "[null]", 6);
    env_len = master->env ? 9 : 6;
    for (i = 0; i < (size_t)(width - 8 - env_len); i++)
        write(1, " ", 1);
    write(1, "|\n", 2);
    write(1, "|   errorcode: ", 14);
    errorcode_str = ft_itoa(master->errorcode);
    if (errorcode_str)
    {
        write(1, errorcode_str, ft_strlen(errorcode_str));
        err_len = ft_strlen(errorcode_str);
        free(errorcode_str);
    }
    else
        err_len = 0;
    for (i = 0; i < (size_t)(width - 14 - err_len); i++)
        write(1, " ", 1);
    write(1, "|\n", 2);
    print_border(width, '+', '+', '-');
}