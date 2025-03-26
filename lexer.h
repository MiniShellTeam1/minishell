#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

typedef enum {
    NORMAL,
    IN_SINGLE_QUOTE,
    IN_DOUBLE_QUOTE,
    IN_WORD,
    IN_OPERATOR
} t_state;

typedef struct {
    char    **tokens;
    size_t  count;
    size_t  capacity;
} t_token_list;

t_token_list    *lexer(char const *input);
t_token_list    *init_token_list(void);
int             add_token(t_token_list *tokens, char *buffer);
void            free_token_list(t_token_list *tokens);
int             process_char(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
// State handlers in lexer_utils.c
int             handle_normal(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int             handle_single_quote(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int             handle_double_quote(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int             handle_word(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);
int             handle_operator(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos);

#endif