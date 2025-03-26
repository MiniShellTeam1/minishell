#include <readline/readline.h>
#include <stdio.h>

int main(void)
{
    char *line;

    while ((line = readline("$ ")) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    return (0);
}