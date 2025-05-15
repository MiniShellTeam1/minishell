#include "minishell.h"

static void ft_checknumeric(t_master master, long *errorcode);

void ft_exit(t_master master)
{
    long errorcode;

    if (!master.cmds->args[1])
    {
        master.errorcode = 0;
        exit (0);
    }
/*     if (master.cmds->args[2])
    {
        ft_printerror(master.cmds->args[0], NULL, TOO_MANY_ARGUMENTS);
        master.errorcode = 1;
        exit (1);
    } */
    ft_checknumeric(master, &errorcode);
    ft_putstr_fd("exit\n", 1);
    if (master.cmds->args[2])
    {
        ft_printerror(master.cmds->args[0], NULL, TOO_MANY_ARGUMENTS);
        master.errorcode = 1;
        exit (1);
    }
    master.errorcode = (unsigned char)errorcode;
    exit(master.errorcode);
}

static void ft_checknumeric(t_master master, long *errorcode)
{
    int overflow;
    int x;

    x = 0;
    while (master.cmds->args[1][x] && ((master.cmds->args[1][x] >= '\t' && master.cmds->args[1][x] <= '\r') 
    || master.cmds->args[1][x] == ' '))
        x++;
    if (master.cmds->args[1][x] == '+' || master.cmds->args[1][x] == '-')
        x++;
    while (master.cmds->args[1][x])
    {
        if (master.cmds->args[1][x] < '0' || master.cmds->args[1][x] > '9')
        {
            ft_printerror(master.cmds->args[0], master.cmds->args[1], NUMERIC_ARGUMENT_REQUIRED);
            master.errorcode = 2;
            exit (2);
        }
        x++;
    }
    *errorcode = ft_atol(master.cmds->args[1], &overflow);
    if (overflow == 1)
    {
        ft_printerror(master.cmds->args[0], master.cmds->args[1], NUMERIC_ARGUMENT_REQUIRED);
        master.errorcode = 2;
        exit (2);
    }
}
