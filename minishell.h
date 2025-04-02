#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_command {
    char            *cmdpath;
    char            **cmdargs;
    char            **infiles;
    char            **outfiles;
    char            *errormsg;
    int             append;
    char            *heredoc_input;
    struct s_command *next;
} s_command;

#endif