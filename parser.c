#include "libft/libft.h"
#include "parser.h"
#include "parser_utils.h"

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
    cmd->redirect_in = NULL;
    cmd->redirect_out = NULL;
    cmd->append = 0;
    cmd->pipe_next = 0;
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
    free(cmd->redirect_in);
    free(cmd->redirect_out);
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
    if (i >= 10) // Initial capacity check
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

int process_token(t_command **cmd, char *token, int *pipe_flag)
{
    if (!ft_strncmp(token, "|", 2))
        return (*pipe_flag = 1, 1);
    if (!ft_strncmp(token, ">", 2) || !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<", 2) || !ft_strncmp(token, "<<", 3))
        return (2);
    return (add_arg(*cmd, strip_quotes(token)));
}

t_command *parser(t_token_list *tokens)
{
    t_command   *head;
    t_command   *current;
    size_t      i;
    int         pipe_flag;

    head = init_command();
    if (!head)
        return (NULL);
    current = head;
    i = 0;
    pipe_flag = 0;
    while (i < tokens->count)
    {
        if (process_token(&current, tokens->tokens[i], &pipe_flag) == 2)
        {
            if (!ft_strncmp(tokens->tokens[i], "<<", 3))
                current->redirect_in = ft_strjoin("<<", tokens->tokens[i + 1]);
            else if (!set_redirect(current, tokens->tokens[i], tokens->tokens[i + 1]))
                return (free_command(head), NULL);
            i++;
        }
        else if (pipe_flag)
        {
            current->pipe_next = 1;
            current->next = init_command();
            current = current->next;
            pipe_flag = 0;
        }
        i++;
    }
    return (head);
}