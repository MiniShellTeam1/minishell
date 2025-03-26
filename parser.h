#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

t_command   *parser(t_token_list *tokens);
t_command   *init_command(void);
void        free_command(t_command *cmd);
int         add_arg(t_command *cmd, char *arg);
int         process_token(t_command **cmd, char *token, int *pipe_flag);

#endif