/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:03:39 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * 10);
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->args[0] = NULL;
	cmd->infiles = malloc(sizeof(char *) * 2);
	if (!cmd->infiles)
		return (free(cmd->args), free(cmd), NULL);
	cmd->infiles[0] = NULL;
	cmd->outfiles = malloc(sizeof(char *) * 2);
	if (!cmd->outfiles)
		return (free(cmd->args), free(cmd->infiles), free(cmd), NULL);
	cmd->cmdpath = NULL;
	cmd->errormsg = NULL;
	cmd->append = 0;
	cmd->heredoc_input = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	free_string_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	free_string_array(cmd->args);
	free_string_array(cmd->infiles);
	free_string_array(cmd->outfiles);
	free(cmd->cmdpath);
	free(cmd->errormsg);
	free(cmd->heredoc_input);
	free_command(cmd->next);
	free(cmd);
}

static int	expand_args_array(t_command *cmd, size_t current_size)
{
	char	**new_args;
	size_t	i;

	new_args = malloc(sizeof(char *) * (current_size * 2));
	if (!new_args)
		return (0);
	i = 0;
	while (cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

int	add_arg(t_command *cmd, char *arg)
{
	size_t	i;
	char	*dup;

	if (!arg || arg[0] == '\0')
		return (1);
	dup = ft_strdup(arg);
	if (!dup)
		return (0);
	i = 0;
	while (cmd->args[i])
		i++;
	if (i >= 10)
	{
		if (!expand_args_array(cmd, i))
			return (free(dup), 0);
	}
	cmd->args[i] = dup;
	cmd->args[i + 1] = NULL;
	return (1);
}
