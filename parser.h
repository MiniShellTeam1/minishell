#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

s_command   *parser(t_token_list *tokens);
s_command   *init_command(void);
void        free_command(s_command *cmd);
int         add_arg(s_command *cmd, char *arg);
int         process_token(s_command **cmd, char *token, int *pipe_flag);

#endif