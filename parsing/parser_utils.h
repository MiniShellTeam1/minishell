#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

#include "parser.h"
#include "../libft/libft.h" 

char *strip_quotes(char *token);
int is_variable(char *token);
char *expand_variable(char *token);
int set_redirect(t_command *cmd, char *token, char *next_token);

#endif