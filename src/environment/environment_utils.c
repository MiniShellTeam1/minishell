#include "minishell.h"

/* returns a string created before the '=' sign */

char *ft_getkey(char *var)
{
	int x;
	char *key;

	x = 0;
	while (var[x] && var[x] != '=')
		x++;
	key = malloc(sizeof(char) * x + 1);
	if (!key)
		return (NULL);
	x = 0;
	while (var[x] && var[x] != '=')
	{
		key[x] = var[x];
		x++;
	}
	key[x] = 0;
	return (key);
}

/* returns a string created after the '=' sign  */

char *ft_getvalue(char *var)
{
	int x;
	int y;
	char *value;

	x = 0;
	y = 0;
	while (var[x] && var[x] != '=')
		x++;
	if (var[x] == '=')
		x++;
	while (var[x + y])
		y++;
	value = malloc(sizeof(char) * y + 1);
	if (!value)
		return (NULL);
	y = 0;
  	while (var[x])
	{
		value[y] = var[x];
		y++;
		x++;
	}
	value[y] = 0;
	return (value);
}

/* frees the given variable */

void ft_freevar(t_env *var)
{
	if (var)
	{
    	if (var->key)
        	free(var->key);
    	if (var->value)
        	free(var->value);
        free(var);
	}
}

/* takes the string of $SHLVL and checks if +1 is in ranged of maximum SHLVL
if it is adds +1 and sets it back into a string */

char *ft_addlvl(char *stringlvl)
{
    int shlvl;
    char *newstringlvl;

    shlvl = atoi(stringlvl); //!replace with our atoi from libft
	free(stringlvl);
    if (shlvl < 0)
        shlvl = 0;
    else if (shlvl + 1 >= 1000)
    {
        ft_printerror("warning", NULL, "minishell level too high, resetting to 1\n");
        shlvl = 1;
    }
    else
        shlvl++;
    newstringlvl = ft_itoa(shlvl); //!replace with our itoa from libft
    return (newstringlvl);
}

void ft_freeenv(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

char **ft_getenvarray(t_master *master)
{
	t_env *tmp;
	char **envarr;
	int x;

	x = 0;
	envarr = malloc(sizeof(char *) * (ft_lstlen(*master) + 1));
	if (!envarr)
		return (NULL);
	tmp = master->env;
	while (tmp)
	{
		envarr[x] = malloc(sizeof(char) * (ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2)); //!protecten!!!
		envarr[x] = ft_strjoin3(tmp->key, "=", tmp->value); //! protecten!!!!
		x++;
		tmp = tmp->next;
	}
	envarr[x] = NULL;
	return (envarr);
}

int ft_lstlen(t_master master)
{
	int x;

	x = 0;
	while (master.env)
	{
		x++;
		master.env = master.env->next;
	}
	return (x);
}

t_env *ft_getvar(t_env *env, char *key)
{
	t_env *tmpenv;

	tmpenv = env;
	while (tmpenv)
	{
		if (!ft_strcmp(tmpenv->key, key))
			return (tmpenv);
		tmpenv = tmpenv->next;
	}
	return (NULL);
}