#include "executor.h"
#include "errormsg.h"

void ft_execbuiltin(t_master *master);
void ft_execpipe(t_master *master);
int ft_isbuiltin(t_command cmd);
void ft_checkcmdpath(t_master *master, t_command currentcmd);

void ft_exec(t_master *master)
{
	if (master->cmds->next && master->cmds->next->args || !ft_isbuiltin(*master->cmds))
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
	int x;
	int pipes[4];

	x = 0;
	while (master->cmds && master->cmds->args)
	{
		if (x % 2 == 0 && master->cmds->next->args)
		{
			printf("%d\n", x);
			write(1, "open pipe1\n", 12);
			pipe(&pipes[0]);
		}
		else if (x % 2 != 0 && master->cmds->next->args)
		{
			printf("%d\n", x);
			write(1, "open pipe2\n", 12);
			pipe(&pipes[2]);
		}
		master->pids[++pid] = fork();
		if (master->pids[pid] == -1)
			ft_freeandexit(master, 1);
		if (master->pids[pid] == 0)
		{
			infilefd = ft_openinfiles(master, *master->cmds);
			outfilefd = ft_openoutfiles(master, *master->cmds);
			ft_checkcmdpath(master, *master->cmds);
			if (infilefd)
			{
				printf("%d\n", x);
				write(1, "dup infile\n", 12);
				dup2(infilefd, STDOUT_FILENO);
			}
			else if (!infilefd && x != 0 && x % 2 != 0)
			{
				printf("%d\n", x);
				write(1, "dup pipe1\n", 11);
				dup2(pipes[0], STDIN_FILENO);
			}
			else if (!infilefd && x != 0 && x % 2 == 0)
			{
				printf("%d\n", x);
				write(1, "dup pipe2\n", 11);
				dup2(pipes[2], STDIN_FILENO);
			}
			if (outfilefd)
			{
				printf("%d\n", x);
				write(1, "dup outfile\n", 13);
				dup2(outfilefd, STDOUT_FILENO);
			}
			else if (!outfilefd && master->cmds && x % 2 == 0)
			{
				printf("%d\n", x);
				write(1, "dup pipe1 out\n", 15);
				dup2(pipes[1], STDOUT_FILENO);
			}
			else if (!outfilefd && master->cmds->next->args && master->cmds && x % 2 != 0)
			{
				printf("%d\n", x);
				write(1, "dup pipe2 out\n", 15);
				dup2(pipes[3], STDOUT_FILENO);
			}
 			if (x % 2 == 0 && master->cmds)
			{
				close(pipes[0]);
				//close(pipes[1]);
			}
			if (x % 2 != 0 && master->cmds)
			{
				close(pipes[2]);
				close(pipes[1]);
			}
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
		x++;
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
	//else if (!ft_strcmp(master->cmds->args[0], "cd"))
		//ft_cd(master);
	//else if (!ft_strcmp(master->cmds->args[0], "echo"))
		//ft_echo(master);
	//else if (!ft_strcmp(master->cmds->args[0], "exit"))
		//ft_exit(master);
	else if (!ft_strcmp(master->cmds->args[0], "env"))
		ft_env(*master);
}
