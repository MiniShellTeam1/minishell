#include "executor.h"

void ft_export(t_master *master) //!not finished yet
{
    if (!master->cmds->args[1])
        while (master->env)
        {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(master->env->key, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(master->env->value, 1);
            ft_putstr_fd("\n", 1);
            master->env = master->env->next;
        }
}