/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:47:21 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_command_path(t_command *cmd, t_master *master)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin_command(cmd->args[0]))
	{
		set_builtin_path(cmd);
		return ;
	}
	if (is_absolute_or_relative_path(cmd->args[0]))
	{
		validate_direct_path(cmd);
		return ;
	}
	resolve_command_in_path(cmd, master);
}

int	is_builtin_command(const char *cmd_name)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	int			i;

	if (!cmd_name)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp((char *)cmd_name, (char *)builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

void	set_builtin_path(t_command *cmd)
{
	if (cmd->cmdpath)
		free(cmd->cmdpath);
	cmd->cmdpath = ft_strdup(cmd->args[0]);
	if (cmd->errormsg)
	{
		free(cmd->errormsg);
		cmd->errormsg = NULL;
	}
}

int	is_absolute_or_relative_path(const char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (cmd_name[0] == '/')
		return (1);
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		return (1);
	if (cmd_name[0] == '.' && cmd_name[1] == '.' && cmd_name[2] == '/')
		return (1);
	return (0);
}

void	validate_direct_path(t_command *cmd)
{
	if (access(cmd->args[0], F_OK) != 0)
	{
		set_command_error(cmd, "No such file or directory");
		return ;
	}
	if (access(cmd->args[0], X_OK) != 0)
	{
		set_command_error(cmd, "Permission denied");
		return ;
	}
	if (cmd->cmdpath)
		free(cmd->cmdpath);
	cmd->cmdpath = ft_strdup(cmd->args[0]);
}
