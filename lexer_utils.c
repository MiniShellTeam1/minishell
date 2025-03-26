#include "lexer.h"

int handle_normal(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos)
{
    if (**input == ' ')
        return ((*input)++, 1);
    if (**input == '"')
        return (*state = IN_DOUBLE_QUOTE, buffer[(*buf_pos)++] = *(*input)++, 1);
    if (**input == '\'')
        return (*state = IN_SINGLE_QUOTE, buffer[(*buf_pos)++] = *(*input)++, 1);
    if (**input == '|' || **input == '<' || **input == '>')
        return (*state = IN_OPERATOR, buffer[(*buf_pos)++] = *(*input)++, 1);
    return (*state = IN_WORD, buffer[(*buf_pos)++] = *(*input)++, 1);
}

int handle_single_quote(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos)
{
    buffer[(*buf_pos)++] = **input;
    if (**input == '\'')
    {
        *state = NORMAL;
        if (!add_token(tokens, buffer))
            return (0);
        *buf_pos = 0;
    }
    (*input)++;
    return (1);
}

int handle_double_quote(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos)
{
    buffer[(*buf_pos)++] = **input;
    if (**input == '"')
    {
        *state = NORMAL;
        if (!add_token(tokens, buffer))
            return (0);
        *buf_pos = 0;
    }
    (*input)++;
    return (1);
}

int handle_word(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos)
{
    if (**input == ' ' || **input == '|' || **input == '<' || **input == '>')
    {
        *state = NORMAL;
        if (!add_token(tokens, buffer))
            return (0);
        *buf_pos = 0;
        return (1);
    }
    buffer[(*buf_pos)++] = *(*input)++;
    return (1);
}

int handle_operator(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos)
{
    if (*buf_pos == 1 && (buffer[0] == '>' && **input == '>') || (buffer[0] == '<' && **input == '<'))
        buffer[(*buf_pos)++] = *(*input)++;
    else
    {
        *state = NORMAL;
        if (!add_token(tokens, buffer))
            return (0);
        *buf_pos = 0;
    }
    return (1);
}