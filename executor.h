#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

typedef struct s_command {
    char **args;
}   t_command;

void ft_printerror(char *cmd, char *errfile, char *errormsg);
void ft_putstr_fd(char *str, int fd);

#endif