/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:02 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 14:10:49 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/libft.h"
#include "lexer_utils.h"

int	handle_normal(t_state *state, char const **input, t_token_list *tokens,
		char *buffer, size_t *buf_pos)
{
	(void)tokens;
	if (**input == ' ')
	{
		(*input)++;
		return (1);
	}
	if (**input == '"')
		return (*state = IN_DOUBLE_QUOTE, buffer[(*buf_pos)++] = *(*input)++,
			1);
	if (**input == '\'')
		return (*state = IN_SINGLE_QUOTE, buffer[(*buf_pos)++] = *(*input)++,
			1);
	if (**input == '|' || **input == '<' || **input == '>')
		return (*state = IN_OPERATOR, buffer[(*buf_pos)++] = *(*input)++, 1);
	return (*state = IN_WORD, buffer[(*buf_pos)++] = *(*input)++, 1);
}

int	handle_single_quote(t_state *state, char const **input,
		t_token_list *tokens, char *buffer, size_t *buf_pos)
{
	buffer[(*buf_pos)++] = **input;
	write(1, "In handle_single_quote, char: ", 30);
	write(1, *input, 1);
	write(1, "\n", 1);
	write(1, "Before increment, **input: ", 27);
	if (**input == '\0')
		write(1, "END", 3);
	else
		write(1, *input, 1);
	write(1, "\n", 1);
	(*input)++;
	if (**input == '\0')
	{
		*state = NORMAL;
		buffer[*buf_pos] = '\0';
		write(1, "handle_single_quote adding token (end of input): ", 48);
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		if (!add_token(tokens, buffer))
			return (0);
		*buf_pos = 0;
		return (1);
	}
	if (**input == '\'')
	{
		*state = NORMAL;
		buffer[*buf_pos] = '\0';
		write(1, "handle_single_quote adding token: ", 34);
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		if (!add_token(tokens, buffer))
			return (0);
		*buf_pos = 0;
	}
	return (1);
}

int	handle_double_quote(t_state *state, char const **input,
		t_token_list *tokens, char *buffer, size_t *buf_pos)
{
	buffer[(*buf_pos)++] = **input;
	write(1, "In handle_double_quote, char: ", 30);
	write(1, *input, 1);
	write(1, "\n", 1);
	write(1, "Before increment, **input: ", 27);
	if (**input == '\0')
		write(1, "END", 3);
	else
		write(1, *input, 1);
	write(1, "\n", 1);
	(*input)++;
	if (**input == '\0')
	{
		*state = NORMAL;
		buffer[*buf_pos] = '\0';
		write(1, "handle_double_quote adding token (end of input): ", 48);
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		if (!add_token(tokens, buffer))
			return (0);
		*buf_pos = 0;
		return (1);
	}
	if (**input == '"')
	{
		*state = NORMAL;
		buffer[*buf_pos] = '\0';
		write(1, "handle_double_quote adding token: ", 34);
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		if (!add_token(tokens, buffer))
			return (0);
		*buf_pos = 0;
	}
	else if (**input == '|' || **input == '<' || **input == '>')
	{
		*state = NORMAL;
		buffer[*buf_pos] = '\0';
		write(1, "handle_double_quote adding token (redirect/pipe): ", 50);
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		if (!add_token(tokens, buffer))
			return (0);
		*buf_pos = 0;
		return (1);
	}
	return (1);
}

int	handle_word(t_state *state, char const **input, t_token_list *tokens,
		char *buffer, size_t *buf_pos)
{
	if (**input == ' ' || **input == '|' || **input == '<' || **input == '>')
	{
		*state = NORMAL;
		buffer[*buf_pos] = '\0';
		write(1, "handle_word adding token: ", 26);
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		if (!add_token(tokens, buffer))
			return (0);
		*buf_pos = 0;
		return (1);
	}
	buffer[(*buf_pos)++] = *(*input)++;
	return (1);
}

int	handle_operator(t_state *state, char const **input, t_token_list *tokens,
		char *buffer, size_t *buf_pos)
{
	if (*buf_pos == 1 && ((buffer[0] == '>' && **input == '>')
			|| (buffer[0] == '<' && **input == '<')))
		buffer[(*buf_pos)++] = *(*input)++;
	else
	{
		*state = NORMAL;
		buffer[*buf_pos] = '\0';
		write(1, "handle_operator adding token: ", 30);
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		if (!add_token(tokens, buffer))
			return (0);
		*buf_pos = 0;
	}
	return (1);
}