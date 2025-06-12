/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:05:35 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unclosed_quotes(t_lexer_data *data)
{
	if (*(data->state) == IN_SINGLE_QUOTE || *(data->state) == IN_DOUBLE_QUOTE)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		cleanup_lexer(data);
		return (0);
	}
	return (1);
}

static int	process_lexer_loop(t_lexer_data *data)
{
	while (get_current_char(data))
	{
		if (!process_char(data))
		{
			cleanup_lexer(data);
			return (0);
		}
	}
	return (1);
}

t_token_list	*lexer(const char *input)
{
	t_lexer_data	data;
	t_token_list	*tokens;

	if (!input)
		return (NULL);
	tokens = init_token_list();
	if (!tokens)
		return (NULL);
	if (!init_lexer_data(&data, input, tokens))
	{
		free_token_list(tokens);
		return (NULL);
	}
	if (!process_lexer_loop(&data) || !check_unclosed_quotes(&data))
	{
		free_token_list(tokens);
		return (NULL);
	}
	finalize_token(&data);
	cleanup_lexer(&data);
	return (tokens);
}

int	process_char(t_lexer_data *data)
{
	t_state	current_state;

	current_state = *(data->state);
	if (current_state == NORMAL)
		return (handle_normal(data));
	if (current_state == IN_SINGLE_QUOTE)
		return (handle_single_quote(data));
	if (current_state == IN_DOUBLE_QUOTE)
		return (handle_double_quote(data));
	if (current_state == IN_WORD)
		return (handle_word(data));
	if (current_state == IN_OPERATOR)
		return (handle_operator_state(data));
	return (lexer_error("Invalid lexer state"));
}
