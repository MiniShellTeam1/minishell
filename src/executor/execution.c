/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:22:41 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:22:51 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execbuiltin(t_master *master);
void	ft_execpipe(t_master *master);
int		ft_isbuiltin(t_command cmd);
void	ft_checkcmdpath(t_master *master, t_command *currentcmd);

int		ft_countcmd(t_command *cmds);

void	ft_exec(t_master *master)
{
	int	infilefd;
	int	outfilefd;
	int	saved_stdin;
	int	saved_stdout;
	int	i;
	int	status;

	if ((master->cmds->next && master->cmds->next->args)
		|| !ft_isbuiltin(*master->cmds))
		ft_execpipe(master);
	else
	{
		infilefd = ft_openinfiles(master, *master->cmds);
		if (infilefd == -1)
			return ;
		outfilefd = ft_openoutfiles(master, *master->cmds);
		if (outfilefd == -1)
			return ;
		if (infilefd > 0)
		{
			saved_stdin = dup(STDIN_FILENO);
			dup2(infilefd, STDIN_FILENO);
			close(infilefd);
		}
		if (outfilefd > 0)
		{
			saved_stdout = dup(STDOUT_FILENO);
			dup2(outfilefd, STDOUT_FILENO);
			close(outfilefd);
		}
		ft_execbuiltin(master);
		if (infilefd > 0) /* FIX: Check > 0, not just truthy */
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		if (outfilefd > 0) /* FIX: Check > 0, not just truthy */
		{
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
		}
	}
	i = 0;
	while (master->pids && master->pids[i])
	{
		waitpid(master->pids[i], &status, 0);
		i++;
	}
	if (master->pids)
	{
		free(master->pids);
		master->pids = NULL;
	}
	if (i)
		master->errorcode = WEXITSTATUS(status);
}

void	ft_execpipe(t_master *master)
{
	int		pipes[2][2];
	int		infilefd;
	int		outfilefd;
	char	**env;
	int		x;

	x = 0;
	/* FIX: Initialize pipes array */
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
	master->pids = malloc(sizeof(pid_t) * (ft_countcmd(master->cmds) + 1));
	if (!master->pids)
		ft_freeandexit(master, 1);
	master->pids[ft_countcmd(master->cmds)] = 0;
	while (master->cmds && master->cmds->args)
	{
		if (master->cmds->next && master->cmds->next->args)
		{
			if (pipe(pipes[x % 2]) == -1)
			{
				perror("pipe");
				ft_freeandexit(master, 1);
			}
		}
		master->pids[x] = fork();
		if (master->pids[x] == -1)
		{
			perror("fork");
			ft_freeandexit(master, 1);
		}
		if (master->pids[x] == 0) /* Child process */
		{
			infilefd = ft_openinfiles(master, *master->cmds);
			if (infilefd == -1)
				ft_freeandexit(master, master->errorcode);
			outfilefd = ft_openoutfiles(master, *master->cmds);
			if (outfilefd == -1)
				ft_freeandexit(master, master->errorcode);
			ft_checkcmdpath(master, master->cmds);
			/* Set up stdin */
			if (infilefd > 0)
			{
				if (dup2(infilefd, STDIN_FILENO) == -1)
				{
					perror("dup2 stdin");
					ft_freeandexit(master, 1);
				}
				close(infilefd);
			}
			else if (x > 0)
			{
				if (dup2(pipes[(x + 1) % 2][0], STDIN_FILENO) == -1)
				{
					perror("dup2 pipe stdin");
					ft_freeandexit(master, 1);
				}
			}
			/* Set up stdout */
			if (outfilefd > 0)
			{
				if (dup2(outfilefd, STDOUT_FILENO) == -1)
				{
					perror("dup2 stdout");
					ft_freeandexit(master, 1);
				}
				close(outfilefd);
			}
			else if (master->cmds->next)
			{
				if (dup2(pipes[x % 2][1], STDOUT_FILENO) == -1)
				{
					perror("dup2 pipe stdout");
					ft_freeandexit(master, 1);
				}
			}
			/* Close ALL pipe file descriptors in child */
			if (pipes[0][0] != -1)
				close(pipes[0][0]);
			if (pipes[0][1] != -1)
				close(pipes[0][1]);
			if (pipes[1][0] != -1)
				close(pipes[1][0]);
			if (pipes[1][1] != -1)
				close(pipes[1][1]);
			env = ft_getenvarray(master);
			if (!env)
				ft_freeandexit(master, 1);
			if (ft_isbuiltin(*master->cmds))
			{
				ft_execbuiltin(master);
				ft_freechararr(env);
				exit(master->errorcode);
			}
			else
			{
				execve(master->cmds->cmdpath, master->cmds->args, env);
				perror("execve");
				ft_freechararr(env);
				ft_freeandexit(master, 127);
			}
		}
		/* Parent process - close unused pipe ends */
		if (x > 0)
		{
			close(pipes[(x + 1) % 2][0]);
			close(pipes[(x + 1) % 2][1]);
		}
		master->cmds = master->cmds->next;
		x++;
	}
	/* Close remaining pipes in parent */
	if (pipes[0][0] != -1)
		close(pipes[0][0]);
	if (pipes[0][1] != -1)
		close(pipes[0][1]);
	if (pipes[1][0] != -1)
		close(pipes[1][0]);
	if (pipes[1][1] != -1)
		close(pipes[1][1]);
}

int	ft_countcmd(t_command *cmds)
{
	int			count;
	t_command	*tmp;

	tmp = cmds;
	count = 0;
	while (tmp) /* FIX: Count ALL commands, not just non-builtins */
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_execbuiltin(t_master *master)
{
	if (!ft_strcmp(master->cmds->args[0], "unset"))
		master->errorcode = ft_unset(master);
	else if (!ft_strcmp(master->cmds->args[0], "export"))
		master->errorcode = ft_export(master);
	else if (!ft_strcmp(master->cmds->args[0], "pwd"))
		master->errorcode = ft_pwd();
	else if (!ft_strcmp(master->cmds->args[0], "cd"))
		master->errorcode = ft_cd(master);
	else if (!ft_strcmp(master->cmds->args[0], "echo"))
		master->errorcode = ft_echo(*master->cmds);
	else if (!ft_strcmp(master->cmds->args[0], "exit"))
		ft_exit(*master);
	else if (!ft_strcmp(master->cmds->args[0], "env"))
		master->errorcode = ft_env(*master);
}

char	**ft_getpathsarr(t_master master)
{
	char	**paths;
	t_env	*path_var;

	/* FIX: Use ft_getvar instead of manual traversal */
	path_var = ft_getvar(master.env, "PATH");
	if (path_var)
	{
		paths = ft_split(path_var->value, ':');
		if (!paths)
			ft_freeandexit(&master, 1);
		return (paths);
	}
	paths = malloc(sizeof(char *));
	if (!paths)
		ft_freeandexit(&master, 1);
	*paths = NULL;
	return (paths);
}

void	ft_checkforcmdpath(t_master *master, t_command *currentcmd)
{
	int x;
	char **paths;
	char cwd[1024];

	x = 0;
	paths = ft_getpathsarr(*master);
	if (!paths)
		ft_freeandexit(master, 1);

	if (currentcmd->args && (currentcmd->args[0][0] == '.'
			|| currentcmd->args[0][0] == '/'))
	{
		if (access(currentcmd->args[0], X_OK) == 0)
		{
			currentcmd->cmdpath = ft_getstralloc(currentcmd->args[0]);
			ft_freechararr(paths);
			return ;
		}
		else
		{
			ft_printerror(currentcmd->args[0], NULL, NO_SUCH_FILE_OR_DIRECTORY);
			ft_freechararr(paths);
			ft_freeandexit(master, 127);
		}
	}

	while (paths && paths[x])
	{
		currentcmd->cmdpath = ft_strjoin3(paths[x], "/", currentcmd->args[0]);
		if (!currentcmd->cmdpath)
		{
			ft_freechararr(paths);
			ft_freeandexit(master, 1);
		}
		if (access(currentcmd->cmdpath, X_OK) == 0)
		{
			ft_freechararr(paths);
			return ;
		}
		free(currentcmd->cmdpath);
		x++;
	}
	ft_freechararr(paths);

	if (getcwd(cwd, sizeof(cwd)))
	{
		currentcmd->cmdpath = ft_strjoin3(cwd, "/", currentcmd->args[0]);
		if (!currentcmd->cmdpath)
			ft_freeandexit(master, 1);
	}
	else
	{
		currentcmd->cmdpath = NULL;
	}
}