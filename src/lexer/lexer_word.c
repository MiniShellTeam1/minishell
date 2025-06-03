/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 09:06:50 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_word(t_lexer_data *data)
{
	char	current_char;

	current_char = get_current_char(data);
	if (check_word_end(current_char))
	{
		*(data->state) = NORMAL;
		return (1);
	}
	if (current_char == '\'' || current_char == '"')
		return (handle_word_quote(data));
	if (is_operator_char(current_char))
		return (handle_word_operator(data));
	if (!add_char_to_buffer(data, current_char))
		return (0);
	return (advance_input(data));
}

int	add_char_to_buffer(t_lexer_data *data, char c)
{
	if (!data || !data->buffer || !data->buf_pos)
		return (0);
	if (*(data->buf_pos) >= BUFFER_SIZE - 1)
		return (0);
	data->buffer[*(data->buf_pos)] = c;
	(*(data->buf_pos))++;
	return (1);
}

int	check_word_end(char current_char)
{
	if (current_char == ' ' || current_char == '\t')
		return (1);
	if (current_char == '\0')
		return (1);
	return (0);
}

int	handle_word_quote(t_lexer_data *data)
{
	char	current_char;

	current_char = get_current_char(data);
	if (current_char == '\'')
		*(data->state) = IN_SINGLE_QUOTE;
	else if (current_char == '"')
		*(data->state) = IN_DOUBLE_QUOTE;
	if (!add_char_to_buffer(data, current_char))
		return (0);
	return (advance_input(data));
}

int	handle_word_operator(t_lexer_data *data)
{
	*(data->state) = NORMAL;
	return (1);
}