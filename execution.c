#include "executor.h"
#include "errormsg.h"

int ft_execbuiltin(t_master *master);
void ft_execpipe(t_master *master);

/* void ft_exec(t_master *master)
{
	if (master->cmds->next)
		ft_execpipe(master);
	else
		if (!ft_execbuiltin(master));
			ft_execpipe(master);
} */

void ft_execpipe(t_master *master)
{
	int pid; //! durch pid array in master ersetzen
	int infilefd;
	int outfilefd;

	while (master->cmds)
	{
		pid = fork();
		if (pid > 0)
		{
			//infilefd = ft_openinfiles(master);
			//outfilefd = ft_openoutfiles(master); //! muss noch geschrieben werden
			//ft_checkcmdpath(master); //! muss noch geschrieben werden
			execve(master->cmds->cmdpath, master->cmds->args, ft_getenvarray(master)); //!muss noch geschrieben werden
			close (infilefd);
			close (outfilefd);
			ft_freeenv(master);
			//ft_freecmds(master); //!muss noch geschrieben werden
			free(master);
		}
		master->cmds = master->cmds->next;
	}
}


int ft_openinfiles(t_master *master)
{
	int x;
	int fd;

	x = 0;
	while (master->cmds->infiles[x])
	{
		fd = open(master->cmds->infiles[x], O_RDWR);
		if (access(master->cmds->infiles[x], F_OK) < 0)
		{
			ft_printerror(master->cmds->args[0], master->cmds->infiles[x], NO_SUCH_FILE_OR_DIRECTORY);
			master->errorcode = 1;
		}
		else if (fd == -1)
		{
			ft_printerror(master->cmds->args[0], master->cmds->infiles[x], PERMISSION_DENIED);
			master->errorcode = 1;
		}
		else if (master->cmds->infiles[x + 1])
			close (fd);
		x++;
	} //! if fd is -1 need to free everything and exit with errorcode
	return (fd);
}
/* 
int ft_execbuiltin(t_master *master)
{
	int isbuiltin;

	isbuiltin = 0;
	if (master->cmds->args[0])
	{
		if (!ft_strcmp(master->cmds->args[0], "unset") && ++isbuiltin)
			ft_unset(master);
		else if (!ft_strcmp(master->cmds->args[0], "export") && ++isbuiltin)
			ft_export(master);
		else if (!ft_strcmp(master->cmds->args[0], "pwd") && ++isbuiltin)
			ft_pwd();
		else if (!ft_strcmp(master->cmds->args[0], "cd") && ++isbuiltin)
			ft_cd(master);
		else if (!ft_strcmp(master->cmds->args[0], "echo") && ++isbuiltin)
			ft_echo(master);
		else if (!ft_strcmp(master->cmds->args[0], "exit") && ++isbuiltin)
			ft_exit(master);
		else if (!ft_strcmp(master->cmds->args[0], "env") && ++isbuiltin)
			ft_env(*master);
	}
	return (isbuiltin);
} */
