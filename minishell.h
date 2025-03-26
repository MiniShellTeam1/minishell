#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_command {
    char            **args;
    char            *redirect_in;
    char            *redirect_out;
    int             append;
    int             pipe_next;
    struct s_command *next;
} t_command;

#endif