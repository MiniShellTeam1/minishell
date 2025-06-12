/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_priority.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 17:20:15 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_input_files(t_command *cmd)
{
	if (cmd->infiles)
	{
		ft_freechararr(cmd->infiles);
		cmd->infiles = malloc(sizeof(char *) * 2);
		if (cmd->infiles)
			cmd->infiles[0] = NULL;
	}
}

static void	clear_heredoc_content(t_command *cmd)
{
	if (cmd->heredoc_input)
	{
		free(cmd->heredoc_input);
		cmd->heredoc_input = NULL;
	}
	cmd->is_heredoc = 0;
}

void	clear_previous_input_redirections(t_command *cmd)
{
	clear_input_files(cmd);
	clear_heredoc_content(cmd);
}

int	add_input_redirect_priority(t_command *cmd, char *filename, t_master *master)
{
	char	*processed_filename;

	clear_previous_input_redirections(cmd);
	processed_filename = process_word_complete(filename, master);
	if (!processed_filename)
		return (0);
	if (!append_to_string_array(&cmd->infiles, processed_filename))
	{
		free(processed_filename);
		return (0);
	}
	free(processed_filename);
	return (1);
}
