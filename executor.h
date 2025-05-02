#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>

#include <stdio.h>

typedef struct s_master {
    struct s_command *cmds;
    struct s_env *env;
    int *pids;
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

//error
void ft_printerror(char *cmd, char *errfile, char *errormsg);

//libft
void ft_putstr_fd(char *str, int fd);
int ft_strcmp(char *str1, char *str2);
char *ft_itoa(int num);
int ft_strlen(char *str);
int ft_strncmp(char *str1, char *str2, int n);
int ft_strchr(char *str, char c);
char *ft_strjoin3(char *str1, char *str2, char *str3);

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
char **ft_getenvarray(t_master *master);
int ft_lstlen(t_master master);

//builtins
void ft_env(t_master master);
void ft_unset(t_master *master);
void ft_export(t_master *master);
int ft_pwd();
int ft_cd(t_master *master);
void ft_exit(t_command cmd);
void ft_echo(t_command cmd);

//execution
void ft_exec(t_master *master);
void ft_execpipe(t_master *master);
void ft_execbuiltin(t_master *master);

//execution utils
int ft_openinfiles(t_master *master, t_command currentcmd);
int ft_openoutfiles(t_master *master, t_command currentcmd);
void ft_checkcmdpath(t_master *master, t_command currentcmd);
int ft_isbuiltin(t_command cmd);

//free
void ft_freeandexit(t_master *master, unsigned char exitcode);
void ft_freecmds(t_master *master);
void ft_freechararr(char **array);

#endif