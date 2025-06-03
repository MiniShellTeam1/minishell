/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 08:18:26 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_normal(t_lexer_data *data)
{
	char	current_char;

	current_char = get_current_char(data);
	if (current_char == ' ' || current_char == '\t')
		return (handle_whitespace(data));
	if (current_char == '\'' || current_char == '"')
		return (handle_quote_start(data));
	if (is_operator_char(current_char))
		return (handle_operator(data));
	return (handle_word_start(data));
}

int	handle_whitespace(t_lexer_data *data)
{
	char	current_char;

	if (!finalize_token(data))
		return (0);
	current_char = get_current_char(data);
	while (current_char == ' ' || current_char == '\t')
	{
		if (!advance_input(data))
			break ;
		current_char = get_current_char(data);
	}
	return (1);
}

int	handle_quote_start(t_lexer_data *data)
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

int	handle_operator(t_lexer_data *data)
{
	if (!finalize_token(data))
		return (0);
	*(data->state) = IN_OPERATOR;
	if (!add_char_to_buffer(data, get_current_char(data)))
		return (0);
	return (advance_input(data));
}

int	handle_word_start(t_lexer_data *data)
{
	*(data->state) = IN_WORD;
	if (!add_char_to_buffer(data, get_current_char(data)))
		return (0);
	return (advance_input(data));
}