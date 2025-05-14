#include "minishell.h"

void ft_execbuiltin(t_master *master);
void ft_execpipe(t_master *master);
int ft_isbuiltin(t_command cmd);
void ft_checkcmdpath(t_master *master, t_command *currentcmd);

int ft_countcmd(t_command *cmds);

void ft_exec(t_master *master)
{
    int infilefd;
    int outfilefd;
    int saved_stdin;
    int saved_stdout;

	if ((master->cmds->next && master->cmds->next->args) || !ft_isbuiltin(*master->cmds))
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
            close (infilefd);
        }
        if (outfilefd > 0)
        {
            saved_stdout = dup(STDOUT_FILENO);
            dup2(outfilefd, STDOUT_FILENO);
            close (outfilefd);
        }
		ft_execbuiltin(master);
        if (infilefd)
        {
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
        }
        if (outfilefd)
        {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }
    }
    int i = 0;
    int status;
    while (master->pids && master->pids[i])
    {
        waitpid(master->pids[i], &status, 0);
        i++;
    }
    if (i)
        master->errorcode = WEXITSTATUS(status);
} 
void ft_execpipe(t_master *master)
{
    int pipes[2][2];
    int infilefd;
	int outfilefd;
    char **env;
    int x;

	x = 0;
    master->pids = malloc(sizeof(pid_t) * ft_countcmd(master->cmds) + 1);
    master->pids[ft_countcmd(master->cmds)] = 0;
    while (master->cmds && master->cmds->args)
    {
        if (master->cmds->next && master->cmds->next->args)
            if (pipe(pipes[x % 2]) == -1)
                ft_freeandexit(master, 1);
        master->pids[x] = fork();
        if (master->pids[x] == -1)
            ft_freeandexit(master, 1);
        if (master->pids[x] == 0)
        {
            infilefd = ft_openinfiles(master, *master->cmds);
            if (infilefd == -1)
                ft_freeandexit(master, master->errorcode);
            outfilefd = ft_openoutfiles(master, *master->cmds);
            if (outfilefd == -1)
                ft_freeandexit(master, master->errorcode);
            ft_checkcmdpath(master, master->cmds);
            if (infilefd > 0)
                dup2(infilefd, STDIN_FILENO); //! protecten nicht vergessen
            else if (x > 0)
                dup2(pipes[(x + 1) % 2][0], STDIN_FILENO); //! protecten nicht vergessen
            if (outfilefd > 0)
                dup2(outfilefd, STDOUT_FILENO); //! protecten nicht vergessen
            else if (master->cmds->next)
                dup2(pipes[x % 2][1], STDOUT_FILENO); //! protecten nicht vergessen
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
                ft_execbuiltin(master);
            else
                execve(master->cmds->cmdpath, master->cmds->args, env);
			if (infilefd > 0)
            	close(infilefd);
            if (outfilefd > 0)
				close(outfilefd);
            ft_freechararr(env);
            ft_freeandexit(master, 1);
        }
        if (x > 0)
        {
            close(pipes[(x + 1) % 2][0]);
            close(pipes[(x + 1) % 2][1]);
        }
        if (!master->cmds->next)
        {
            close(pipes[x % 2][0]);
            close(pipes[x % 2][1]);
        }
        master->cmds = master->cmds->next;
        x++;
    }
}

int ft_countcmd(t_command *cmds)
{
    int count;
    t_command *tmp;

    tmp = cmds;
    count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
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
		ft_echo(*master->cmds);
    else if (!ft_strcmp(master->cmds->args[0], "exit"))
		ft_exit(*master);
	else if (!ft_strcmp(master->cmds->args[0], "env"))
		ft_env(*master);
}

char	**ft_getpathsarr(t_master master)
{
	char	**paths;
    
	while (master.env->next)
	{
		if (!ft_strcmp(master.env->key, "PATH"))
        {
			paths = ft_split(master.env->value, ':');
            if (!paths)
                ft_freeandexit(&master, 1);
			return (paths);
        }
        master.env = master.env->next;
    }
	return (NULL);
}

/* checks for the finalpath access */

void	ft_checkforcmdpath(t_master *master, t_command *currentcmd)
{
	int		x;
    char **paths;
    char cwd[1024];

	x = 0;
    paths = ft_getpathsarr(*master);
    if (!paths)
    {
        ft_freeandexit(master, 1);
    }
    if (access(currentcmd->args[0], X_OK) == 0)
    {
        currentcmd->cmdpath = ft_getstralloc(currentcmd->args[0]);
        return ;
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
			return ;
		free(currentcmd->cmdpath);
		x++;
	}
    ft_freechararr(paths);
    if (!getcwd(cwd, sizeof(cwd)))
    {
        currentcmd->cmdpath = NULL;
        return ;
    }
    currentcmd->cmdpath = ft_strjoin3(cwd, "/", currentcmd->args[0]);
	if (!currentcmd->cmdpath)
		ft_freeandexit(master, 1);
}
