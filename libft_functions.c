#include "executor.h"

void ft_putstr_fd(char *str, int fd)
{
    int x;

    x = 0;
    while (str[x])
    {
        write(fd, &str[x], 1);
        x++;
    }
}