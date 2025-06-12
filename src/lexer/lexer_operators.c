/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:41:24 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator_state(t_lexer_data *data)
{
	char	current_char;

	current_char = get_current_char(data);
	if (is_double_operator(data, current_char))
		return (handle_double_operator(data));
	if (!finalize_token(data))
		return (0);
	*(data->state) = NORMAL;
	return (1);
}

int	is_double_operator(t_lexer_data *data, char current_char)
{
	char	prev_char;

	if (*(data->buf_pos) != 1)
		return (0);
	prev_char = data->buffer[0];
	if (prev_char == '<' && current_char == '<')
		return (1);
	if (prev_char == '>' && current_char == '>')
		return (1);
	return (0);
}

int	handle_double_operator(t_lexer_data *data)
{
	if (!add_char_to_buffer(data, get_current_char(data)))
		return (0);
	if (!advance_input(data))
		return (0);
	if (!finalize_token(data))
		return (0);
	*(data->state) = NORMAL;
	return (1);
}

int	is_valid_operator_sequence(const char *sequence)
{
	if (!sequence)
		return (0);
	if (ft_strncmp(sequence, "|", 1) == 0)
		return (1);
	if (ft_strncmp(sequence, "<", 1) == 0)
		return (1);
	if (ft_strncmp(sequence, ">", 1) == 0)
		return (1);
	if (ft_strncmp(sequence, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(sequence, ">>", 2) == 0)
		return (1);
	return (0);
}

int	get_operator_length(const char *input)
{
	if (!input)
		return (0);
	if ((input[0] == '<' && input[1] == '<') || (input[0] == '>'
			&& input[1] == '>'))
		return (2);
	if (input[0] == '|' || input[0] == '<' || input[0] == '>')
		return (1);
	return (0);
}
