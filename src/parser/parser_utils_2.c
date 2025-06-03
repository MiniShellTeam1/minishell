

#include "minishell.h"

void set_command_error(t_command *cmd, const char *error_msg)
{
    if (cmd->errormsg)
        free(cmd->errormsg);
    cmd->errormsg = ft_strdup(error_msg);
}

void resolve_command_in_path(t_command *cmd, t_master *master)
{
    if (!cmd || !master)
        return;
    ft_checkforcmdpath(master, cmd);
}