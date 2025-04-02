#include "libft.h"
#include "parser.h"
#include "parser_utils.h"

s_command *init_command(void)
{
    s_command   *cmd;

    cmd = malloc(sizeof(s_command));
    if (!cmd)
        return (NULL);
    cmd->cmdargs = malloc(sizeof(char *) * 10);
    if (!cmd->cmdargs)
        return (free(cmd), NULL);
    cmd->cmdargs[0] = NULL;
    cmd->infiles = malloc(sizeof(char *) * 2);
    if (!cmd->infiles)
        return (free(cmd->cmdargs), free(cmd), NULL);
    cmd->infiles[0] = NULL;
    cmd->outfiles = malloc(sizeof(char *) * 2);
    if (!cmd->outfiles)
        return (free(cmd->cmdargs), free(cmd->infiles), free(cmd), NULL);
    cmd->outfiles[0] = NULL;
    cmd->cmdpath = NULL;
    cmd->errormsg = NULL;
    cmd->append = 0;
    cmd->heredoc_input = NULL;
    cmd->next = NULL;
    return (cmd);
}

void free_command(s_command *cmd)
{
    size_t  i;

    if (!cmd)
        return ;
    i = 0;
    while (cmd->cmdargs[i])
        free(cmd->cmdargs[i++]);
    free(cmd->cmdargs);
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

int add_arg(s_command *cmd, char *arg)
{
    size_t  i;
    char    *dup;
    char    **new_args;

    dup = ft_strdup(arg);
    if (!dup)
        return (0);
    i = 0;
    while (cmd->cmdargs[i])
        i++;
    if (i >= 10)
    {
        new_args = malloc(sizeof(char *) * (i * 2));
        if (!new_args)
            return (free(dup), 0);
        i = 0;
        while (cmd->cmdargs[i])
        {
            new_args[i] = cmd->cmdargs[i];
            i++;
        }
        free(cmd->cmdargs);
        cmd->cmdargs = new_args;
    }
    cmd->cmdargs[i] = dup;
    cmd->cmdargs[i + 1] = NULL;
    return (1);
}

int process_token(s_command **cmd, char *token, int *pipe_flag)
{
    char *expanded;

    if (!ft_strncmp(token, "|", 2))
    {
        *pipe_flag = 1;
        return (1);
    }
    if (!ft_strncmp(token, ">", 2) || !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<", 2) || !ft_strncmp(token, "<<", 3))
        return (2);
    expanded = expand_variable(token);
    if (!expanded)
        return (0);
    return (add_arg(*cmd, strip_quotes(expanded)));
}

static int is_builtin(const char *cmd)
{
    const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", "cat", NULL}; // Added "cat" as placeholder
    int i = 0;

    while (builtins[i])
    {
        if (!ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1))
            return (1);
        i++;
    }
    return (0);
}

static void validate_command(s_command *cmd)
{
    if (cmd->cmdargs[0])
    {
        if (is_builtin(cmd->cmdargs[0]))
        {
            cmd->cmdpath = ft_strdup(cmd->cmdargs[0]);
            cmd->errormsg = NULL;
        }
        else
        {
            cmd->cmdpath = NULL;
            cmd->errormsg = ft_strdup("command not found");
        }
    }
}

s_command *parser(t_token_list *tokens)
{
    s_command   *head;
    s_command   *current;
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
        result = process_token(&current, tokens->tokens[i], &pipe_flag);
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
            validate_command(current); // Validate new command block
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
            // Token was added by process_token, no need to add again
        }
        i++;
    }
    validate_command(head); // Validate the first command block
    validate_command(current); // Validate the last command block
    return (head);
}