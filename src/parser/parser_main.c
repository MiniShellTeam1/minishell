/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:01:00 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parser(t_token_list *tokens, t_master *master)
{
	t_command		*head;
	t_parser_state	state;

	if (!tokens || !master)
		return (NULL);
	if (!init_parser_state(&state, tokens, master))
		return (NULL);
	head = build_command_list(&state);
	cleanup_parser_state(&state);
	return (head);
}

t_command	*build_command_list(t_parser_state *state)
{
	t_command	*head;
	t_command	*current;

	head = init_command();
	if (!head)
		return (NULL);
	current = head;
	while (state->token_index < state->tokens->count)
	{
		if (!process_command_token(state, current))
		{
			free_command(head);
			return (NULL);
		}
	}
	finalize_commands(head, state->master);
	return (head);
}

int	process_command_token(t_parser_state *state, t_command *current)
{
	if (!process_next_token(state, current))
		return (0);
	if (is_pipe_token(state))
	{
		current = handle_pipe_transition(state, current);
		if (!current)
			return (0);
	}
	return (1);
}

int	process_next_token(t_parser_state *state, t_command *cmd)
{
	char	*token;

	token = get_current_token(state);
	if (!token)
		return (0);
	if (is_redirect_token(token))
		return (handle_redirection(state, cmd));
	if (is_pipe_token(state))
		return (advance_token_index(state));
	return (add_command_argument(state, cmd));
}

void	finalize_commands(t_command *head, t_master *master)
{
	t_command	*current;

	current = head;
	while (current)
	{
		validate_command_path(current, master);
		current = current->next;
	}
}
