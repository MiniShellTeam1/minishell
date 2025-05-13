#include "minishell.h"

static int ft_countargs(char **args);
static int ft_checkminusnl(char **args);
static void ft_printargs(int nlparam, int argsnum, char **args);

/* prints out the arguments given if its not a valid -n flag */

void ft_echo(t_command cmd)
{
    int argsnum;
    int nlparam;

    argsnum = ft_countargs(cmd.args);
    nlparam = ft_checkminusnl(cmd.args);
    ft_printargs(nlparam, argsnum, cmd.args);
}

/* counts the amount of arguments given */

static int ft_countargs(char **args)
{
    int x;

    x = 0;
    while (args[x])
        x++;
    return (x);
}

/* checks if there are any -n / -nnnnn arguments and returns the number of -n / -nnnnn arguments found */

static int ft_checkminusnl(char **args)
{
    int x;
    int y;
    int nlparam;

    x = 1;
    nlparam = 0;
    while (args[x])
    {
        y = 0;
        if (args[x][y] == '-')
        {
            y++;
            while (args[x][y] && args[x][y] == 'n')
                y++;
        }
        if (y >= 2 && !args[x][y])
            nlparam++;
        else
            break;
        x++;
    }
    return (nlparam);
}

/* prints out the given arguments to the terminal, jumps over the -n / -nnnnn flags */

static void ft_printargs(int nlparam, int argsnum, char **args)
{
    int x;

    x = 1;
    if (argsnum == 1)
    {
        write(1, "\n", 1);
        return ;
    }
    if (argsnum - nlparam == 1)
        return ;
    if (nlparam > 0)
        x += nlparam;
    while (args[x])
    {
        ft_putstr_fd(args[x], 1);
        if (x < argsnum - 1)
            write(1, " ", 1);
        x++;
    }
    if (nlparam == 0)
        write(1, "\n", 1);
}