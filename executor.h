#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <readline/readline.h>

#include <stdio.h>

typedef struct s_master {
    struct s_command *cmds;
    struct s_env *env;
    unsigned char errorcode;
}   t_master;

typedef struct s_command {
    char *cmdpath;
    char **args;
    char **infiles;
    char **outfiles;
    char *errormsg;
    int append;

    struct s_command *next;
}   t_command;

typedef struct s_env {
    char *key;
    char *value;

	struct s_env *prev;
    struct s_env *next;
}   t_env;

void ft_printerror(char *cmd, char *errfile, char *errormsg);

//env
void ft_env(t_master master);

//libft
void ft_putstr_fd(char *str, int fd);
int ft_strcmp(char *str1, char *str2);
char *ft_itoa(int num);
int ft_strlen(char *str);
int ft_strncmp(char *str1, char *str2, int n);

//enviroment
t_env *ft_createenvlist(char **envp);
void ft_addvar(t_env **env, char *key, char *value);
void ft_delvar(t_env **env, char *key);

//enviroment utils
char *ft_getkey(char *var);
char *ft_getvalue(char *var);
void ft_freevar(t_env *var);
char *ft_addlvl(char *stringlvl);
void ft_freeenv(t_master *master);
char *ft_getstralloc(char *str);

#endif