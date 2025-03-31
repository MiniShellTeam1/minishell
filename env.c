#include "executor.h"
#include <stdio.h>

int ft_strcmp(char *str1, char *str2);
char *ft_getkey(char *var);
char *ft_getvalue(char *var);
void ft_addvar(t_env **env, char *key, char *value);
void ft_delvar(t_env *env, char *key);


t_env *ft_createenvlist(char **envp)
{
	int x;
	t_env *env;

	env = NULL;
	x = 0;
	while (envp[x])
	{
		ft_addvar(&env, ft_getkey(envp[x]), ft_getvalue(envp[x]));
		x++;
	}
	return (env);
}

char *ft_getkey(char *var)
{
	int x;
	char *key;

	x = 0;
	while (var[x] && var[x] != '=')
		x++;
	key = malloc(sizeof(char) * x + 1);
	x = 0;
	while (var[x] && var[x] != '=')
	{
		key[x] = var[x];
		x++;
	}
	key[x] = 0;
	return (key);
}

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

void ft_addvar(t_env **env, char *key, char *value)
{
	t_env *addedvar;

	addedvar = malloc(sizeof(t_env));
	if (!addedvar)
		return ;
	addedvar->key = key;
	addedvar->value = value;
	addedvar->next = NULL;
	if (!*env)
	{
		env = &addedvar;
		addedvar->prev = NULL;
	}
	else
	{
		addedvar->prev = *env;
		(*env)->next = addedvar;
	}
}

void ft_delvar(t_env *env, char *key)
{
	int x;
	t_env *tmp;

	x = 0;
	while(env)
	{
		if (!ft_strcmp(env->key, key))
		{
			tmp = env;
			env = env->next;
			//ft_freevar(tmp);
			break;
		}
		env = env->next;
	}
}

int ft_strcmp(char *str1, char *str2)
{
	int x;

	x = 0;
	while(str1[x] && str2[x])
	{
		if (str1[x] != str2[x])
			return (1);
		x++;
	}
	return (0);
}

int main(int argc, char **args, char **envp)
{
	(void)argc;
	(void)args;
	t_env *test = ft_createenvlist(envp);
	printf("%p\n", test);
	return (0);
}