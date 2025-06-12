/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:46:07 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_quote(t_lexer_data *data)
{
	char	current_char;

	current_char = get_current_char(data);
	if (current_char == '\0')
		return (1);
	if (current_char == '\'')
	{
		if (!add_quote_char(data, current_char))
			return (0);
		*(data->state) = IN_WORD;
		return (advance_input(data));
	}
	if (!add_char_to_buffer(data, current_char))
		return (0);
	return (advance_input(data));
}

int	handle_double_quote(t_lexer_data *data)
{
	char	current_char;

	current_char = get_current_char(data);
	if (current_char == '\0')
		return (1);
	if (current_char == '"')
	{
		if (!add_quote_char(data, current_char))
			return (0);
		*(data->state) = IN_WORD;
		return (advance_input(data));
	}
	if (!add_char_to_buffer(data, current_char))
		return (0);
	return (advance_input(data));
}

int	add_quote_char(t_lexer_data *data, char quote_char)
{
	if (!data || !data->buffer || !data->buf_pos)
		return (0);
	if (*(data->buf_pos) >= BUFFER_SIZE - 1)
		return (0);
	data->buffer[*(data->buf_pos)] = quote_char;
	(*(data->buf_pos))++;
	return (1);
}

int	find_closing_quote(t_lexer_data *data, char quote_type)
{
	const char	*temp_input;
	char		current_char;

	temp_input = *(data->input);
	while (*temp_input)
	{
		current_char = *temp_input;
		if (current_char == quote_type)
			return (1);
		temp_input++;
	}
	return (0);
}

int	handle_unclosed_quote(t_lexer_data *data, char quote_type)
{
	(void)data;
	ft_putstr_fd("minishell: unclosed quote: ", 2);
	write(2, &quote_type, 1);
	ft_putstr_fd("\n", 2);
	return (0);
}
