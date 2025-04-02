#include "executor.h"

int main()
{
    char *line;
    while ((line = readline("minishell> ")) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    return (0);
}
