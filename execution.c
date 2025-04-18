#include "executor.h"

int ft_execbuiltin(t_master *master);
void ft_execpipe(t_master *master);

void ft_exec(t_master *master)
{
	if (master->cmds->next)
		ft_execpipe(master);
	else
		if (!ft_execbuiltin(master));
			ft_exec(master);
}

void ft_execpipe(t_master *master)
{
	int pid;
	int infilefd;
	int outfilefd;

	pid = fork();
	if (pid > 0)
	{
		infilefd = ft_openinfiles(master); //! muss noch fertig geschrieben werden
		outfilefd = ft_openoutfiles(master); //! muss noch geschrieben werden
		ft_checkcmdpath(master);
		execve(master->cmds->cmdpath, master->cmds->args, ft_getenvarray(master)); //!muss noch geschrieben werden
		close (infilefd);
		close (outfilefd);
		ft_freeenv(master);
		ft_freecmds(master); //!muss noch geschrieben werden
		free(master);
	}
}

int ft_openinfiles(t_master *master)
{
	int x;
	int fd;

	x = 0;
	while (master->cmds->infiles[x + 1])
	{
		if (access(master->cmds->infiles[x], F_OK) < 0)
			ft_printerror(master->cmds->args[0], master->cmds->infiles[x], "No such file or directory");
		fd = open(master->cmds->infiles[x], O_RDWR);
		if (fd == -1)
			ft_printerror(master->cmds->args[0], master->cmds->infiles[x], "Permission denied");
	}
	fd = open(master->cmds->infiles[x], O_RDWR);
	if ()
	return (fd);
}

int ft_execbuiltin(t_master *master)
{
	int isbuiltin;

	isbuiltin = 0;
	if (master->cmds->args[0])
	{
		if (!ft_strcmp(master->cmds->args[0], "unset") && isbuiltin++)
			ft_unset(master);
		else if (!ft_strcmp(master->cmds->args[0], "export") && isbuiltin++)
			ft_export(master);
		else if (!ft_strcmp(master->cmds->args[0], "pwd") && isbuiltin++)
			ft_pwd();
		else if (!ft_strcmp(master->cmds->args[0], "cd") && isbuiltin++)
			ft_cd(master);
		else if (!ft_strcmp(master->cmds->args[0], "echo") && isbuiltin++)
			ft_echo(master);
		else if (!ft_strcmp(master->cmds->args[0], "exit") && isbuiltin++)
			ft_exit(master);
		else if (!ft_strcmp(master->cmds->args[0], "env") && isbuiltin++)
			ft_env(*master);
	}
	return (isbuiltin);
}
