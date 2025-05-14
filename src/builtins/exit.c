#include "minishell.h"

long ft_atol(char *str, int *overflow);
static void ft_checknumeric(t_master master, long *errorcode);

void ft_exit(t_master master)
{
    long errorcode;

    if (!master.cmds->args[1])
    {
        master.errorcode = 0;
        exit (0);
    }
    if (master.cmds->args[2])
    {
        ft_printerror(master.cmds->args[0], NULL, TOO_MANY_ARGUMENTS);
        master.errorcode = 1;
        exit (1);
    }
    ft_checknumeric(master, &errorcode);
    ft_putstr_fd("exit\n", 1);
    master.errorcode = (unsigned char)errorcode;
    exit(master.errorcode);
}

static void ft_checknumeric(t_master master, long *errorcode)
{
    int overflow;
    int x;

    x = 0;
    while (master.cmds->args[1][x])
    {
        if (master.cmds->args[1][x] <= '0' || master.cmds->args[1][x] >= '9')
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

long ft_atol(char *str, int *overflow)
{
    long result;
    int sign;
    int digit;
    
    result = 0;
    sign = 1;
    *overflow = 0;
    while ((*str >= '\a' && *str <= '\n') || *str == ' ')
        str ++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        digit = *str - '0';
        if (sign == 1)
        {
            if (result > (LONG_MAX - digit) / 10)
            {
                *overflow = 1;
                return (0);
            }
        }
        else
        {
            if (result > (-(LONG_MIN + digit)) / 10)
            {
                *overflow = 1;
                return (0);
            }
        }
        result = result * 10 + digit;
        str++;
    }
    return (sign * result);
}
