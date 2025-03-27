#include "executor.h"

#include <stdio.h>

void ft_echo(t_command);
static int ft_getargs(char **args);
static int ft_getnl(char **args);
void ft_printargs(int nlparam, int argsnum, char **args);

void ft_echo(t_command cmd)
{
    int argsnum;
    int nlparam;

    argsnum = ft_getargs(cmd.args);
    nlparam = ft_getnl(cmd.args);
    ft_printargs(nlparam, argsnum, cmd.args);
}

static int ft_getargs(char **args)
{
    int x;

    x = 0;
    while (args[x])
        x++;
    return (x);
}

static int ft_getnl(char **args)
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
        if (y >= 1 && !args[x][y])
            nlparam++;
        else
            break;
        x++;
    }
    return (nlparam);
}

void ft_printargs(int nlparam, int argsnum, char **args)
{
    int x;

    x = 1;
    if (argsnum == 1)
        printf("\n");
    if (argsnum - nlparam == 1)
        return ;
    if (nlparam > 0)
        x += nlparam;
    while (args[x])
    {
        printf("%s", args[x]);
        if (x < argsnum - 1)
            printf(" ");
        x++;
    }
    if (nlparam == 0)
        printf("\n");
}
