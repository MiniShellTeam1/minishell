#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"
# include "lexing/lexer.h"

void debug_print_tokens(t_token_list *tokens);
void debug_print_command(t_command *cmd);
void debug_print_master(t_master *master);

#endif