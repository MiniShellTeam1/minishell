#include "minishell.h"

static void	ft_printexport(t_master *master);
static void	ft_exportvar(t_master *master);
static int	ft_changeifexist(t_master *master, char *vararg);
int			ft_checkexportvar(char *str);

/* exports a given variable with its value or just prints out
the export list */

int	ft_export(t_master *master)
{
	ft_printexport(master);
	ft_exportvar(master);
	return (0);
}

/* prints the enviroment list sorted by value of the key */
//! 25lines
static void	ft_printexport(t_master *master)
{
	char	*lastprinted;
	t_env	*min;
	t_env	*tmp;
	int		i;
	int		lstlen;

	i = 0;
	tmp = master->env;
	lstlen = ft_lstlen(*master);
	lastprinted = NULL;
	if (!master->cmds->args[1])
		while (i < lstlen)
		{
			tmp = master->env;
			min = NULL;
			while (tmp)
			{
				if (!lastprinted || strcmp(tmp->key, lastprinted) > 0)
					//! durch eigenes strcmp ersetzen welches den wertunterschied zurückgibt und nicht wie meines nur 1 oder 0
					if (!min || strcmp(tmp->key, min->key) < 0)       
						//! durch eigenes strcmp ersetzen welches den wertunterschied zurückgibt und nicht wie meines nur 1 oder 0
						min = tmp;
				tmp = tmp->next;
			}
			if (min)
			{
				if (!ft_strcmp(min->key, "_"))
				{
					lastprinted = min->key;
					continue ;
				}
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(min->key, 1);
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(min->value, 1);
				ft_putstr_fd("\"\n", 1);
				lastprinted = min->key;
			}
			i++;
		}
}

/* export the variable if it contains an equal sign, if it already exists
it will get overwritten */

static void	ft_exportvar(t_master *master)
{
	int	x;

	x = 1;
	while (master->cmds->args[x])
	{
		if (!ft_checkexportvar(master->cmds->args[x]))
		{
			if (!ft_changeifexist(master, master->cmds->args[x]))
				ft_addvar(&master->env, ft_getkey(master->cmds->args[x]),
					ft_getvalue(master->cmds->args[x]));
		}
		else if (ft_checkexportvar(master->cmds->args[x]) == 1)
		{
			master->errorcode = 1;
			ft_printerror(master->cmds->args[0], master->cmds->args[x],
				NOT_A_VALID_IDENTIFIER);
		}
		x++;
	}
}

int	ft_checkexportvar(char *str)
{
	if (*str == '=' || (*str >= '0' && *str <= '9'))
		return (1);
	while (*str)
	{
		if ((*str < 'A' || (*str > 'Z' && *str < 'a') || *str > 'z')
			&& (*str < '0' || *str > '9') && *str != '_' && *str != '=')
			return (1);
		if (*str == '=')
			return (0);
		str++;
	}
	return (2);
}

/* checks if the variable already exists in the env list, if so it will get
overwritten and returns a 1 for overwritten */

static int	ft_changeifexist(t_master *master, char *vararg)
{
	int		varlen;
	t_env	*tmp;

	varlen = 0;
	tmp = master->env;
	while (vararg[varlen] != '=')
		varlen++;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == varlen && !ft_strncmp(tmp->key, vararg,
				varlen))
		{
			free(tmp->value);
			tmp->value = ft_getvalue(vararg);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
