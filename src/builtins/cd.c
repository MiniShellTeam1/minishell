// #include "minishell.h"

// static int ft_checkdir(t_command *cmd);
// static int ft_checkargs(t_command *cmd);

// /* builtin cd function like in bash */

// int ft_cd(t_master *master)
// {
//     if (ft_checkargs(master->cmds) || ft_checkdir(master->cmds) || chdir(master->cmds->args[1]) == -1)
//         return (1);
//     ft_setoldpwd(&master);
//     ft_setpwd(&master, master->cmds->args[1]);
//     return (0);
// }

// /* checks the arguments of cd | if there is no or more than 1 */

// static int ft_checkargs(t_command *cmd)
// {
//     if (cmd->args[2])
//     {
//         ft_printerror(cmd->args[0], NULL, TOO_MANY_ARGUMENTS);
//         return (1);
//     }
//     if (!cmd->args[1])
//     {
//         if (chdir(getenv("HOME")) == -1)
//         {
//             ft_printerror(cmd->args[0], "$HOME", NO_SUCH_FILE_OR_DIRECTORY);
//             return (1);
//         }
//     }
//     return (0);
// }

// /* checks if the directory can be opened if not prints error and returns 1 */

// static int ft_checkdir(t_command *cmd)
// {
//     DIR *dir;

//     dir = opendir(cmd->args[1]);
//     if (!dir)
//     {
//         if (errno == ENOTDIR)
//             ft_printerror(cmd->args[0], cmd->args[1], NOT_A_DIRECTORY);
//         else if (errno == ENOENT)
//             ft_printerror(cmd->args[0], cmd->args[1], NO_SUCH_FILE_OR_DIRECTORY);
//         else if (errno == EACCES)
//             ft_printerror(cmd->args[0], cmd->args[1], PERMISSION_DENIED);
//         else if (errno == E2BIG)
//             ft_printerror(cmd->args[0], cmd->args[1], ARGUMENT_LIST_TOO_LONG);
//         else if (errno == ELOOP)
//             ft_printerror(cmd->args[0], cmd->args[1], TOO_MANY_LEVELS_OF_SYMB_LINK);
//         else if (errno == ENAMETOOLONG)
//             ft_printerror(cmd->args[0], cmd->args[1], FILE_NAME_TOO_LONG);
//         return (1);
//     }
//     closedir(dir);
//     return (0);
// }

// /* sets the OLDPWD in the enviroment if PWD var exists else empty string */

// void ft_setoldpwd(t_master *master)
// {
//     t_env *tmp;
//     char cwd[1024];

//     tmp = master->env;
//     while (tmp && !ft_strcmp(tmp->key, "PWD"))
//         tmp = tmp->next;
//     while (master->env && !ft_strcmp(master->env, "OLDPWD"))
//         master->env = master->env->next;
//     if (tmp && master->env)
//     {
//         free(master->env->value);
//         master->env->value = tmp->value;
//     }
//     else if (tmp)
//         ft_addvar(master->env, "OLDPWD", tmp->value);
//     else if (master->env)
//     {
//         free(master->env->value);
//         ft_addvar(master->env, "OLDPWD", "");
//     }
// }

// void ft_setpwd(t_master *master, char *newpwd)
// {
//     while (master->env && ft_strcmp(master->env->value, "PWD"))
//         master->env = master->env->next;
//     if (master->env)
//     {
        
//     }
// }