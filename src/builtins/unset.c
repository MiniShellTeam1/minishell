#include "minishell.h"

int	ft_unset(t_master *master)
{
	int	x;

	x = 1;
	while (master->cmds->args[x])
	{
		ft_delvar(&master->env, master->cmds->args[x]);
		x++;
	}
	return (0);
}
