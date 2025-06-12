/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argumenst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:59:43 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_split_args(t_command *cmd, char **split_args)
{
	size_t	i;

	i = 0;
	while (split_args[i])
	{
		if (!add_arg(cmd, split_args[i]))
		{
			ft_freechararr(split_args);
			return (0);
		}
		i++;
	}
	ft_freechararr(split_args);
	return (1);
}

static int	handle_expandable_arg(t_command *cmd, char *processed_token,
		char *original_token)
{
	char	**split_args;

	if (should_split_field(original_token, 0))
	{
		split_args = split_fields(processed_token);
		if (split_args)
			return (process_split_args(cmd, split_args));
		else
			return (add_arg(cmd, ""));
	}
	else
		return (add_arg(cmd, processed_token));
}

static int	add_processed_argument(t_parser_state *state, t_command *cmd,
		char *token, char *processed_token)
{
	int	result;

	if (has_expandable_variables(token))
		result = handle_expandable_arg(cmd, processed_token, token);
	else
		result = add_arg(cmd, processed_token);
	free(processed_token);
	if (!result)
		return (0);
	return (advance_token_index(state));
}

int	add_command_argument(t_parser_state *state, t_command *cmd)
{
	char	*token;
	char	*processed_token;

	token = get_current_token(state);
	if (!token)
		return (0);
	processed_token = process_word_complete(token, state->master);
	if (!processed_token)
		return (0);
	return (add_processed_argument(state, cmd, token, processed_token));
}
