#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "parser.h"

char    *strip_quotes(char *token);
int     is_variable(char *token);
int     set_redirect(t_command *cmd, char *token, char *next_token);

#endif