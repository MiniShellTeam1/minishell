/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 08:23:21 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_token(const char *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token, "<", 2))
		return (1);
	if (!ft_strncmp(token, ">", 2))
		return (1);
	if (!ft_strncmp(token, "<<", 3))
		return (1);
	if (!ft_strncmp(token, ">>", 3))
		return (1);
	return (0);
}

int	is_pipe_token(t_parser_state *state)
{
	char	*token;

	token = get_current_token(state);
	if (!token)
		return (0);
	return (!ft_strncmp(token, "|", 2));
}

char	*get_current_token(t_parser_state *state)
{
	if (!state || !state->tokens)
		return (NULL);
	if (state->token_index >= state->tokens->count)
		return (NULL);
	return (state->tokens->tokens[state->token_index]);
}

int	advance_token_index(t_parser_state *state)
{
	if (!state)
		return (0);
	if (state->token_index < state->tokens->count)
		state->token_index++;
	return (1);
}

t_token_type	get_token_type(const char *token)
{
	if (!token)
		return (TOKEN_UNKNOWN);
	if (!ft_strncmp(token, "|", 2))
		return (TOKEN_PIPE);
	if (!ft_strncmp(token, "<", 2))
		return (TOKEN_REDIRECT_IN);
	if (!ft_strncmp(token, ">", 2))
		return (TOKEN_REDIRECT_OUT);
	if (!ft_strncmp(token, "<<", 3))
		return (TOKEN_HEREDOC);
	if (!ft_strncmp(token, ">>", 3))
		return (TOKEN_APPEND);
	return (TOKEN_WORD);
}