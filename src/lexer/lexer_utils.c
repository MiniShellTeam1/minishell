/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:41:36 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_lexer_data(t_lexer_data *data, const char *input, t_token_list *tokens)
{
	if (!data || !input || !tokens)
		return (0);
	data->input = &input;
	data->tokens = tokens;
	data->buffer = malloc(BUFFER_SIZE);
	if (!data->buffer)
		return (0);
	data->buf_pos = malloc(sizeof(size_t));
	if (!data->buf_pos)
	{
		free(data->buffer);
		return (0);
	}
	data->state = malloc(sizeof(t_state));
	if (!data->state)
	{
		free(data->buffer);
		free(data->buf_pos);
		return (0);
	}
	*(data->buf_pos) = 0;
	*(data->state) = NORMAL;
	return (1);
}

void	cleanup_lexer(t_lexer_data *data)
{
	if (!data)
		return ;
	if (data->buffer)
		free(data->buffer);
	if (data->buf_pos)
		free(data->buf_pos);
	if (data->state)
		free(data->state);
}

int	finalize_token(t_lexer_data *data)
{
	if (!data || *(data->buf_pos) == 0)
		return (1);
	data->buffer[*(data->buf_pos)] = '\0';
	if (!add_token(data->tokens, data->buffer))
		return (0);
	*(data->buf_pos) = 0;
	return (1);
}

void	reset_buffer(t_lexer_data *data)
{
	if (!data || !data->buf_pos)
		return ;
	*(data->buf_pos) = 0;
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
