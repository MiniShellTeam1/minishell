#include "executor.h"

/* prints out error like minishell: cd: test1: No such file or directory */

void ft_printerror(char *cmd, char *errfile, char *errormsg)
{
    ft_putstr_fd("minishell: ", 2);
    if (cmd)
    {
        ft_putstr_fd(cmd, 2);
        write(2, ": ", 2);
    }
    if (errfile)
    {
        ft_putstr_fd(errfile, 2);
        write(2, ": ", 2);
    }
    ft_putstr_fd(errormsg, 2);
}