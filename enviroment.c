#include "executor.h"

/* takes the enviroment as string array and tranforms it into a
linked list and returns that */

t_env *ft_createenvlist(char **envp)
{
	int x;
    int shlvlexist;
	t_env *env;

	env = NULL;
	x = 0;
    shlvlexist = 0;
	if (!envp || !envp[x]) //!PWD setzen
	{
		ft_addvar(&env, "SHLVL", "1");
		return (env);
	}
	while (envp[x])
	{
        if (!ft_strcmp(ft_getkey(envp[x]), "SHLVL"))
        {
            ft_addvar(&env, ft_getkey(envp[x]), ft_addlvl(ft_getvalue(envp[x])));
            shlvlexist++;
        }
        else
		    ft_addvar(&env, ft_getkey(envp[x]), ft_getvalue(envp[x]));
		x++;
	}
    if (!shlvlexist)
        ft_addvar(&env, "SHLVL", "1");
	return (env);
}

/* adds a variable to the enviroment linked list at the end */

void ft_addvar(t_env **env, char *key, char *value)
{
	t_env *addedvar;
	t_env *temp = *env;

	addedvar = malloc(sizeof(t_env));
	if (!addedvar)
		return ;
	addedvar->key = key;
	addedvar->value = value;
	addedvar->next = NULL;
	if (!*env || !env)
	{
		*env = addedvar;
		addedvar->prev = NULL;
	}
	else
	{
        while (temp->next)
            temp = temp->next;
        temp->next = addedvar;
        addedvar->prev = temp;
	}
}

/* deletes a variable from the linked list with the right key,
if the key's not found nothing happens */

void ft_delvar(t_env **env, char *key)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, key))
        {
			if (!tmp->next)
			{
				if (!tmp->prev)
					*env = NULL;
				else
					tmp->prev->next = NULL;
			}
			if (!tmp->prev)
			{
				if (!tmp->next)
					*env = NULL;
                else
				{
					*env = tmp->next;
					tmp->next->prev = NULL;
				}
			}
			if (tmp->prev && tmp->next)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			ft_freevar(tmp);
            break;
        }
		tmp = tmp->next;
	}
}
