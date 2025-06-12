#include "minishell.h"

/* freeing everything and exiting with the given exitcode */

void	ft_freeandexit(t_master *master, unsigned char exitcode)
{
	ft_freeenv(master->env);
	ft_freecmds(master);
	free(master);
	exit(exitcode);
}

/* freeing the command struct as a whole */

void	ft_freecmds(t_master *master)
{
	t_command	*tmp;

	tmp = master->cmds;
	while (tmp)
	{
		ft_freechararr(tmp->args);
		ft_freechararr(tmp->infiles);
		ft_freechararr(tmp->outfiles);
		if (tmp->cmdpath)
			free(tmp->cmdpath);
		tmp = tmp->next;
	}
}

/* freeing a whole char array */

void	ft_freechararr(char **array)
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