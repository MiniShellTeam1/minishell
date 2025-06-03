/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 09:40:20 by feanor           ###   ########.fr       */
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
		if (!process_next_token(state, current))
		{
			free_command(head);
			return (NULL);
		}
		if (is_pipe_token(state))
		{
			current = handle_pipe_transition(state, current);
			if (!current)
			{
				free_command(head);
				return (NULL);
			}
		}
	}
	finalize_commands(head, state->master);
	return (head);
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

int	add_command_argument(t_parser_state *state, t_command *cmd)
{
	char	*token;
	char	*processed_token;
	char	**split_args;
	size_t	i;

	token = get_current_token(state);
	if (!token)
		return (0);
	
	processed_token = process_word_complete(token, state->master);
	if (!processed_token)
		return (0);
	
	// Check if we need field splitting (unquoted variables)
	if (has_expandable_variables(token) && should_split_field(token, 0))
	{
		split_args = split_fields(processed_token);
		if (split_args)
		{
			i = 0;
			while (split_args[i])
			{
				if (!add_arg(cmd, split_args[i]))
				{
					free(processed_token);
					ft_freechararr(split_args);
					return (0);
				}
				i++;
			}
			ft_freechararr(split_args);
		}
		else
		{
			// No fields after splitting, add empty arg
			if (!add_arg(cmd, ""))
			{
				free(processed_token);
				return (0);
			}
		}
	}
	else
	{
		// No splitting needed
		if (!add_arg(cmd, processed_token))
		{
			free(processed_token);
			return (0);
		}
	}
	
	free(processed_token);
	return (advance_token_index(state));
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