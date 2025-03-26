#include <readline/readline.h>
int main() { char *line; while ((line = readline("$ ")) != NULL) { printf("%s\n", line); free(line); } return 0; }
