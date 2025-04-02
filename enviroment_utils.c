#include "executor.h"

/* returns a string created before the '=' sign */

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
    if (var->key)
        free(var->key);
    if (var->value)
        free(var->value);
    if (var)
        free(var);
}

/* takes the string of $SHLVL and checks if +1 is in ranged of maximum SHLVL
if it is adds +1 and sets it back into a string */

char *ft_addlvl(char *stringlvl)
{
    int shlvl;
    char *newstringlvl;

    shlvl = atoi(stringlvl); //!replace with our atoi from libft
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
