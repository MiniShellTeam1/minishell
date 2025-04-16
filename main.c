#include "executor.h"

int main(int argc, char **argv, char **envp)
{
/*     char *line;
    while ((line = readline("minishell> ")) != NULL)
    {
        printf("%s\n", line);
        free(line);
    } */
	t_master *master = malloc(sizeof(t_master));
	//t_env *env = ft_createenvlist(envp);
	t_env *env = NULL;
	master->env = env;
	ft_freeenv(master);
	free(master);
	return (0);
}
