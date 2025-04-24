#include "executor.h"
#include "errormsg.h"

void ft_execbuiltin(t_master *master);
void ft_execpipe(t_master *master);

void ft_exec(t_master *master)
{
	if (master->cmds->next || !ft_isbuiltin(*master->cmds))
		ft_execpipe(master);
	else if (ft_isbuiltin(*master->cmds))
		ft_execbuiltin(master);
} 

void ft_execpipe(t_master *master)
{
	static int pid = -1;
	int infilefd;
	int outfilefd;
	char **env;

	while (master->cmds)
	{
		master->pids[++pid] = fork();
		if (master->pids[pid] == -1)
			ft_freeandexit(master, 1);
		if (master->pids[pid] == 0)
		{
			infilefd = ft_openinfiles(master, *master->cmds);
			outfilefd = ft_openoutfiles(master, *master->cmds);
			ft_checkcmdpath(master, *master->cmds);
			//! dup2 und pipen
			env = ft_getenvarray(master);
			if (!env)
				ft_freeandexit(master, 1);
			execve(master->cmds->cmdpath, master->cmds->args, env);
			close (infilefd);
			close (outfilefd);
			ft_freechararr(env);
			ft_freeandexit(master, 1);
		}
		master->cmds = master->cmds->next;
	}
}

void ft_checkcmdpath(t_master *master, t_command currentcmd)
{
	if (ft_isbuiltin(currentcmd))
		return ;
	else if (!currentcmd.cmdpath)
	{
		ft_printerror(currentcmd.args[0], NULL, COMMAND_NOT_FOUND);
		ft_freeandexit(master, 127);
	}
	else if (access(currentcmd.cmdpath, X_OK) != 0)
	{
		ft_printerror(currentcmd.args[0], NULL, PERMISSION_DENIED);
		ft_freeandexit(master, 126);
	}
}

int ft_isbuiltin(t_command cmd)
{
	if (cmd.args[0] && (!ft_strcmp(cmd.args[0], "unset") || !ft_strcmp(cmd.args[0], "env") || !ft_strcmp(cmd.args[0], "exit") || 
	!ft_strcmp(cmd.args[0], "export") || !ft_strcmp(cmd.args[0], "echo") || !ft_strcmp(cmd.args[0], "pwd") || !ft_strcmp(cmd.args[0], "cd")))
		return (1);
	return (0);
}

int ft_openinfiles(t_master *master, t_command currentcmd)
{
	int x;
	int fd;

	x = 0;
	if (!currentcmd.infiles[x])
		return (0);
	while (currentcmd.infiles[x])
	{
		fd = open(currentcmd.infiles[x], O_RDWR);
		if (access(currentcmd.infiles[x], F_OK) < 0)
		{
			ft_printerror(NULL, currentcmd.infiles[x], NO_SUCH_FILE_OR_DIRECTORY);
			ft_freeandexit(master, 1);
		}
		else if (fd == -1)
		{
			ft_printerror(NULL, currentcmd.infiles[x], PERMISSION_DENIED);
			ft_freeandexit(master, 1);
		}
		else if (currentcmd.infiles[x + 1])
			close (fd);
		x++;
	}
	return (fd);
}

int ft_openoutfiles(t_master *master, t_command currentcmd)
{
	int x;
	int fd;

	x = 0;
	if (!currentcmd.outfiles[x])
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
			ft_freeandexit(master, 1);
		}
		if (currentcmd.outfiles[x + 1])
			close (fd);
		x++;
	}
	return (fd);
}

void ft_freeandexit(t_master *master, unsigned char exitcode) //! zu free file
{
	ft_freeenv(master);
	ft_freecmds(master);
	free(master);
	exit (exitcode);
}

void ft_freecmds(t_master *master) //! zu free file
{
	t_command *tmp = master->cmds;

	while (tmp)
	{
		ft_freechararr(tmp->args);
		ft_freechararr(tmp->infiles);
		ft_freechararr(tmp->outfiles);
		if (tmp->cmdpath)
			free (tmp->cmdpath);
		tmp = tmp->next;
	}
}

void ft_freechararr(char **array) //! zu free file
{
	int x;

	x = 0;
	if (array)
	{
		while (array[x])
		{
			free(array[x]);
			x++;
		}
		free(array);
	}
}


void ft_execbuiltin(t_master *master)
{
	if (!ft_strcmp(master->cmds->args[0], "unset"))
		ft_unset(master);
	else if (!ft_strcmp(master->cmds->args[0], "export"))
		ft_export(master);
	else if (!ft_strcmp(master->cmds->args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(master->cmds->args[0], "cd"))
		ft_cd(master);
	else if (!ft_strcmp(master->cmds->args[0], "echo"))
		ft_echo(master);
	else if (!ft_strcmp(master->cmds->args[0], "exit"))
		ft_exit(master);
	else if (!ft_strcmp(master->cmds->args[0], "env"))
		ft_env(*master);
}
