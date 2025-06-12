/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 17:19:40 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(t_parser_state *state, t_command *cmd)
{
	char		*redirect_token;
	char		*filename_token;
	t_token_type	type;

	redirect_token = get_current_token(state);
	if (!redirect_token)
		return (0);
	if (!advance_token_index(state))
		return (0);
	filename_token = get_current_token(state);
	if (!filename_token)
		return (0);
	type = get_token_type(redirect_token);
	if (!process_redirect_by_type(cmd, type, filename_token, state->master))
		return (0);
	return (advance_token_index(state));
}

int	process_redirect_by_type(t_command *cmd, t_token_type type, char *filename, t_master *master)
{
	if (type == TOKEN_REDIRECT_IN)
	{
		clear_previous_input_redirections(cmd);
		return (add_input_redirect_priority(cmd, filename, master));
	}
	if (type == TOKEN_REDIRECT_OUT)
		return (add_output_redirect(cmd, filename, master, 0));
	if (type == TOKEN_APPEND)
		return (add_output_redirect(cmd, filename, master, 1));
	if (type == TOKEN_HEREDOC)
		return (add_heredoc_redirect_sequential(cmd, filename, master));
	return (0);
}

int	add_output_redirect(t_command *cmd, char *filename, t_master *master, int append)
{
	char	*processed_filename;

	processed_filename = process_word_complete(filename, master);
	if (!processed_filename)
		return (0);
	if (!append_to_string_array(&cmd->outfiles, processed_filename))
	{
		free(processed_filename);
		return (0);
	}
	cmd->append = append;
	free(processed_filename);
	return (1);
}

int	add_heredoc_redirect_sequential(t_command *cmd, char *delimiter, t_master *master)
{
	char	*processed_delimiter;
	char	*heredoc_token;

	processed_delimiter = process_word_complete(delimiter, master);
	if (!processed_delimiter)
		return (0);
	heredoc_token = ft_strjoin("<<", processed_delimiter);
	free(processed_delimiter);
	if (!heredoc_token)
		return (0);
	if (!append_to_string_array(&cmd->infiles, heredoc_token))
	{
		free(heredoc_token);
		return (0);
	}
	cmd->is_heredoc = 1;
	free(heredoc_token);
	return (1);
}