#include "libft/libft.h"
#include "lexer.h"
#include "lexer_utils.h"

t_token_list *init_token_list(void)
{
    t_token_list    *list;

    list = malloc(sizeof(t_token_list));
    if (!list)
        return (NULL);
    list->tokens = malloc(sizeof(char *) * 10);
    if (!list->tokens)
        return (free(list), NULL);
    list->count = 0;
    list->capacity = 10;
    return (list);
}

int add_token(t_token_list *tokens, char *buffer)
{
    char    **new_tokens;
    char    *token;
    size_t  i;

    token = ft_strdup(buffer);
    if (!token)
        return (0);
    if (tokens->count >= tokens->capacity)
    {
        tokens->capacity *= 2;
        new_tokens = malloc(sizeof(char *) * tokens->capacity);
        if (!new_tokens)
            return (free(token), 0);
        i = 0;
        while (i < tokens->count)
        {
            new_tokens[i] = tokens->tokens[i];
            i++;
        }
        free(tokens->tokens);
        tokens->tokens = new_tokens;
    }
    tokens->tokens[tokens->count] = token;
    tokens->count++;
    return (1);
}

void free_token_list(t_token_list *tokens)
{
    size_t  i;

    i = 0;
    while (i < tokens->count)
    {
        free(tokens->tokens[i]);
        i++;
    }
    free(tokens->tokens);
    free(tokens);
}

int process_char(t_state *state, char const **input, t_token_list *tokens, char *buffer, size_t *buf_pos)
{
    if (*state == NORMAL)
        return (handle_normal(state, input, tokens, buffer, buf_pos));
    if (*state == IN_SINGLE_QUOTE)
        return (handle_single_quote(state, input, tokens, buffer, buf_pos));
    if (*state == IN_DOUBLE_QUOTE)
        return (handle_double_quote(state, input, tokens, buffer, buf_pos));
    if (*state == IN_WORD)
        return (handle_word(state, input, tokens, buffer, buf_pos));
    return (handle_operator(state, input, tokens, buffer, buf_pos));
}

t_token_list *lexer(char const *input)
{
    t_state     state;
    char        *buffer;
    size_t      buf_pos;
    t_token_list    *tokens;

    state = NORMAL;
    buffer = malloc(1024);
    buf_pos = 0;
    tokens = init_token_list();
    if (!buffer || !tokens)
        return (free(buffer), free_token_list(tokens), NULL);
    while (*input)
    {
        if (!process_char(&state, &input, tokens, buffer, &buf_pos))
            return (free(buffer), free_token_list(tokens), NULL);
    }
    if (buf_pos > 0 && state == IN_WORD)
    {
        buffer[buf_pos] = '\0';
        if (!add_token(tokens, buffer))
            return (free(buffer), free_token_list(tokens), NULL);
    }
    return (free(buffer), tokens);
}