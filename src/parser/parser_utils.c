/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 08:23:38 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_parser_state(t_parser_state *state, t_token_list *tokens, t_master *master)
{
	if (!state || !tokens || !master)
		return (0);
	state->tokens = tokens;
	state->master = master;
	state->token_index = 0;
	state->current_cmd = NULL;
	state->error_msg = NULL;
	return (1);
}

void	cleanup_parser_state(t_parser_state *state)
{
	if (!state)
		return ;
	if (state->error_msg)
	{
		free(state->error_msg);
		state->error_msg = NULL;
	}
}

t_command	*handle_pipe_transition(t_parser_state *state, t_command *current)
{
	t_command	*new_cmd;

	if (!advance_token_index(state))
		return (NULL);
	new_cmd = init_command();
	if (!new_cmd)
		return (NULL);
	current->next = new_cmd;
	return (new_cmd);
}

int	append_to_string_array(char ***array, const char *new_item)
{
	char	**new_array;
	size_t	count;
	size_t	i;

	count = get_string_array_length(*array);
	new_array = malloc(sizeof(char *) * (count + 2));
	if (!new_array)
		return (0);
	i = 0;
	while (i < count)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = ft_strdup(new_item);
	if (!new_array[i])
	{
		free(new_array);
		return (0);
	}
	new_array[i + 1] = NULL;
	free(*array);
	*array = new_array;
	return (1);
}

size_t	get_string_array_length(char **array)
{
	size_t	count;

	count = 0;
	if (!array)
		return (0);
	while (array[count])
		count++;
	return (count);
}