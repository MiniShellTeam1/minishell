#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

typedef struct s_master {
    t_command *cmds;
    t_env *env;
    unsigned char errorcode;
}   t_master;

typedef struct s_command {
    char *cmdpath;
    char **args;
    char **infiles;
    char **outfiles;
    char *errormsg;
    int append;

    t_command *next;
}   t_command;

typedef struct s_env {
    char *key;
    char *value;

    t_env *next;
}   t_env;

void ft_printerror(char *cmd, char *errfile, char *errormsg);
void ft_putstr_fd(char *str, int fd);

#endif