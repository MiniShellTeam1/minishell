#include "minishell.h"

/* prints out the whole enviroment */

int ft_env(t_master master)
{ 
 	if (master.cmds->args[1])
		return (1);
	while (master.env)
	{
		ft_putstr_fd(master.env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(master.env->value, 1);
		ft_putstr_fd("\n", 1);
		master.env = master.env->next;
	}
	return (0);
}