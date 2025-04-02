#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_command {
    char            *cmdpath;
    char            **args;
    char            **infiles;
    char            **outfiles;
    char            *errormsg;
    int             append;
    char            *heredoc_input;
    struct s_command *next;
} t_command;

typedef struct s_env {
    // placeholder
} s_env;

typedef struct s_master {
    struct s_command *cmds;
    struct s_env     *env;
    unsigned char    errorcode;
} t_master;

#endif