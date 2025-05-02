/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 17:42:56 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_char(t_lexer_data *data)
{
	if (*(data->state) == NORMAL)
		return (handle_normal(data));
	if (*(data->state) == IN_SINGLE_QUOTE)
		return (handle_single_quote(data));
	if (*(data->state) == IN_DOUBLE_QUOTE)
		return (handle_double_quote(data));
	if (*(data->state) == IN_WORD)
		return (handle_word(data));
	return (handle_operator(data));
}

t_token_list	*lexer(char const *input)
{
	t_state			state;
	char			*buffer;
	size_t			buf_pos;
	t_token_list	*tokens;
	t_lexer_data	data;

	if (!input)
		return (NULL);
	state = NORMAL;
	buffer = malloc(1024);
	if (!buffer)
		return (NULL);
	buf_pos = 0;
	tokens = init_token_list();
	if (!tokens)
	{
		free(buffer);
		return (NULL);
	}
	data.state = &state;
	data.input = &input;
	data.tokens = tokens;
	data.buffer = buffer;
	data.buf_pos = &buf_pos;
	while (*input)
	{
		if (*input == ' ' && state == NORMAL)
		{
			input++;
			if (buf_pos > 0)
			{
				buffer[buf_pos] = '\0';
				if (!add_token(tokens, buffer))
				{
					free(buffer);
					free_token_list(tokens);
					return (NULL);
				}
				buf_pos = 0;
			}
			continue ;
		}
		if (!process_char(&data))
		{
			free(buffer);
			free_token_list(tokens);
			return (NULL);
		}
		if (state == NORMAL && buf_pos > 0)
		{
			buffer[buf_pos] = '\0';
			if (!add_token(tokens, buffer))
			{
				free(buffer);
				free_token_list(tokens);
				return (NULL);
			}
			buf_pos = 0;
		}
	}
	if (buf_pos > 0)
	{
		buffer[buf_pos] = '\0';
		if (!add_token(tokens, buffer))
		{
			free(buffer);
			free_token_list(tokens);
			return (NULL);
		}
	}
	free(buffer);
	return (tokens);
}
