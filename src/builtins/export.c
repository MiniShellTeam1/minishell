#include "minishell.h"

static void ft_printexport(t_master *master);
static void ft_exportvar(t_master *master);
static int ft_changeifexist(t_master *master, char *vararg);
static int ft_checkexportvar(char *str);

int ft_export(t_master *master)
{
	ft_printexport(master);
	ft_exportvar(master);
	return (0);
}

static void ft_printexport(t_master *master)
{
	char *lastprinted;
	t_env *min;
	t_env *tmp;
	int i;
	int lstlen;

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
					if (!min || strcmp(tmp->key, min->key) < 0)
						min = tmp;
				tmp = tmp->next;
			}
			if (min)
			{
				if (!ft_strcmp(min->key, "_"))
				{
					lastprinted = min->key;
					i++;
					continue;
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

static void ft_exportvar(t_master *master)
{
	int x;
	char *key;
	int equals_pos;

	x = 1;
	while (master->cmds->args[x])
	{
		equals_pos = 0;
		while (master->cmds->args[x][equals_pos] && master->cmds->args[x][equals_pos] != '=')
			equals_pos++;
		
		if (master->cmds->args[x][equals_pos] == '=')
		{
			key = malloc(equals_pos + 1);
			if (!key)
			{
				master->errorcode = 1;
				return;
			}
			ft_strlcpy(key, master->cmds->args[x], equals_pos + 1);
			
			if (ft_checkexportvar(key))
			{
				master->errorcode = 1;
				ft_printerror(master->cmds->args[0], master->cmds->args[x], NOT_A_VALID_IDENTIFIER);
				free(key);
			}
			else
			{
				if (!ft_changeifexist(master, master->cmds->args[x]))
					ft_addvar(&master->env, ft_getkey(master->cmds->args[x]), ft_getvalue(master->cmds->args[x]));
				free(key);
			}
		}
		else
		{
			if (ft_checkexportvar(master->cmds->args[x]))
			{
				master->errorcode = 1;
				ft_printerror(master->cmds->args[0], master->cmds->args[x], NOT_A_VALID_IDENTIFIER);
			}
		}
		x++;
	}
}

static int ft_checkexportvar(char *str)
{
	int i;
	
	if (!str || !str[0])
		return (1);
	
	if (str[0] == '=' || (str[0] >= '0' && str[0] <= '9'))
		return (1);
	
	if (!((str[0] >= 'A' && str[0] <= 'Z') || 
		  (str[0] >= 'a' && str[0] <= 'z') || 
		  str[0] == '_'))
		return (1);
	
	i = 1;
	while (str[i])
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || 
			  (str[i] >= 'a' && str[i] <= 'z') || 
			  (str[i] >= '0' && str[i] <= '9') || 
			  str[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

static int ft_changeifexist(t_master *master, char *vararg)
{
	int varlen;
	t_env *tmp;

	varlen = 0;
	tmp = master->env;
	while (vararg[varlen] != '=')
		varlen++;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == varlen && !ft_strncmp(tmp->key, vararg, varlen))
		{
			free(tmp->value);
			tmp->value = ft_getvalue(vararg);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}