/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:41:11 by ncantona          #+#    #+#             */
/*   Updated: 2025/05/13 01:55:41 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tries to open every infile redirection, prints error on error and
returns the last opened filedescriptor */

int ft_openinfiles(t_master *master, t_command currentcmd)
{
	int x;
	int fd;

	x = 0;
	if (!currentcmd.infiles || !currentcmd.infiles[x])
		return (0);
	while (currentcmd.infiles[x])
	{
		fd = open(currentcmd.infiles[x], O_RDWR);
		if (access(currentcmd.infiles[x], F_OK) < 0)
		{
			ft_printerror(NULL, currentcmd.infiles[x], NO_SUCH_FILE_OR_DIRECTORY);
			master->errorcode = 1;
			return (-1);
			//ft_freeandexit(master, 1);
		}
		else if (fd == -1)
		{
			ft_printerror(NULL, currentcmd.infiles[x], PERMISSION_DENIED);
			master->errorcode = 1;
			return (-1);
			//ft_freeandexit(master, 1);
		}
		else if (currentcmd.infiles[x + 1])
			close (fd);
		x++;
	}
	return (fd);
}

/* tries to open every outfileredirection and prints error on error and returns
the last opened filedescriptor */

int ft_openoutfiles(t_master *master, t_command currentcmd)
{
	int x;
	int fd;

	x = 0;
	if (!currentcmd.outfiles || !currentcmd.outfiles[x])
		return (0);
	while (currentcmd.outfiles[x])
	{
		if (currentcmd.outfiles[x + 1])
			fd = open(currentcmd.outfiles[x], O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (currentcmd.append == 0)
			fd = open(currentcmd.outfiles[x], O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (currentcmd.append == 1)
			fd = open(currentcmd.outfiles[x], O_CREAT | O_APPEND | O_RDWR, 0666);
		if (fd == -1)
		{
			ft_printerror(NULL, currentcmd.outfiles[x], PERMISSION_DENIED);
			master->errorcode = 1;
			return (-1);
			//ft_freeandexit(master, 1);
		}
		if (currentcmd.outfiles[x + 1])
			close (fd);
		x++;
	}
	return (fd);
}

/* checks if there is a path to the cmd and prints errormsg on error */

void ft_checkcmdpath(t_master *master, t_command *currentcmd)
{
    if (ft_isbuiltin(*currentcmd))
        return ;
    ft_checkforcmdpath(master, currentcmd);
	if (access(master->cmds->cmdpath, F_OK) != 0)
    {
        ft_printerror(master->cmds->args[0], NULL, COMMAND_NOT_FOUND);
        free(master->cmds->cmdpath);
		master->cmds->cmdpath = NULL;
        ft_freeandexit(master, 127);
    }
    else if (access(master->cmds->cmdpath, X_OK) != 0)
    {
        ft_printerror(master->cmds->args[0], NULL, PERMISSION_DENIED);
        free(master->cmds->cmdpath);
		master->cmds->cmdpath = NULL;
        ft_freeandexit(master, 126);
    }
}

/* checking if the given command is a builtin function */

int ft_isbuiltin(t_command cmd)
{
	if (cmd.args[0] && (!ft_strcmp(cmd.args[0], "unset") || !ft_strcmp(cmd.args[0], "env") || !ft_strcmp(cmd.args[0], "exit") || 
	!ft_strcmp(cmd.args[0], "export") || !ft_strcmp(cmd.args[0], "echo") || !ft_strcmp(cmd.args[0], "pwd") || !ft_strcmp(cmd.args[0], "cd")))
		return (1);
	return (0);
}