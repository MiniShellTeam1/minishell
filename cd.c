#include "executor.h"
#include "errormsg.h"

static int ft_checkdir(t_command cmd);
static int ft_checkargs(t_command cmd);

int ft_cd(t_command cmd)
{
    if (ft_checkargs(cmd) || ft_checkdir(cmd) || chdir(cmd.args[1]) == -1)
        return (1);
    return (0);
}

static int ft_checkargs(t_command cmd)
{
    if (cmd.args[2])
    {
        ft_printerror(cmd.args[0], NULL, TOO_MANY_ARGUMENTS);
        return (1);
    }
    if (!cmd.args[1])
    {
        if (chdir(getenv("HOME")) == -1)
        {
            ft_printerror(cmd.args[0], "$HOME", NO_SUCH_FILE_OR_DIRECTORY);
            return (1);
        }
    }
    return (0);
}

static int ft_checkdir(t_command cmd)
{
    DIR *dir;

    dir = opendir(cmd.args[1]);
    if (!dir)
    {
        if (errno == ENOTDIR)
            ft_printerror(cmd.args[0], cmd.args[1], NOT_A_DIRECTORY);
        else if (errno == ENOENT)
            ft_printerror(cmd.args[0], cmd.args[1], NO_SUCH_FILE_OR_DIRECTORY);
        else if (errno == EACCES)
            ft_printerror(cmd.args[0], cmd.args[1], PERMISSION_DENIED);
        else if (errno == E2BIG)
            ft_printerror(cmd.args[0], cmd.args[1], ARGUMENT_LIST_TOO_LONG);
        else if (errno == ELOOP)
            ft_printerror(cmd.args[0], cmd.args[1], TOO_MANY_LEVELS_OF_SYMB_LINK);
        else if (errno == ENAMETOOLONG)
            ft_printerror(cmd.args[0], cmd.args[1], FILE_NAME_TOO_LONG);
        return (1);
    }
    closedir(dir);
    return (0);
}
