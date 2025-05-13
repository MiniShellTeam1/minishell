#include "minishell.h"

static int ft_checkdir(t_command *cmd);
static int ft_checkargs(t_command *cmd, t_master master);
void ft_setoldpwd(t_master *master);
void ft_setpwd(t_master *master);

/* builtin cd function like in bash */

void ft_cd(t_master *master)
{
    int argenum;

    argenum = ft_checkargs(master->cmds, *master);
    ft_setoldpwd(master);
    if (argenum == 2)
    {
        ft_setpwd(master);
        return ;
    }
    else if (argenum == 1 || ft_checkdir(master->cmds) || chdir(master->cmds->args[1]) == -1)
    {
		master->errorcode = 1;
		return ;
	}
    ft_setpwd(master);
}

/* checks the arguments of cd | if there is no or more than 1 */

static int ft_checkargs(t_command *cmd, t_master master)
{
    t_env *envvar;

    if (cmd->args[2])
    {
        ft_printerror(cmd->args[0], NULL, TOO_MANY_ARGUMENTS);
        return (1);
    }
    if (!cmd->args[1])
    {
        envvar = ft_getvar(master.env, "HOME");
        if (envvar)
        {
            if(chdir(envvar->value) == -1)
                return (1);
            return (2);
        }
        ft_printerror(cmd->args[0], "$HOME", NO_SUCH_FILE_OR_DIRECTORY);
        return (1);
    }
    return (0);
}

/* checks if the directory can be opened if not prints error and returns 1 */

static int ft_checkdir(t_command *cmd)
{
    DIR *dir;

    dir = opendir(cmd->args[1]);
    if (!dir)
    {
        if (errno == ENOTDIR)
            ft_printerror(cmd->args[0], cmd->args[1], NOT_A_DIRECTORY);
        else if (errno == ENOENT)
            ft_printerror(cmd->args[0], cmd->args[1], NO_SUCH_FILE_OR_DIRECTORY);
        else if (errno == EACCES)
            ft_printerror(cmd->args[0], cmd->args[1], PERMISSION_DENIED);
        else if (errno == E2BIG)
            ft_printerror(cmd->args[0], cmd->args[1], ARGUMENT_LIST_TOO_LONG);
        else if (errno == ELOOP)
            ft_printerror(cmd->args[0], cmd->args[1], TOO_MANY_LEVELS_OF_SYMB_LINK);
        else if (errno == ENAMETOOLONG)
            ft_printerror(cmd->args[0], cmd->args[1], FILE_NAME_TOO_LONG);
        return (1);
    }
    closedir(dir);
    return (0);
}

/* sets the OLDPWD in the enviroment list*/

void ft_setoldpwd(t_master *master)
{
    char cwd[1024];
    t_env *oldpwdvar;

    oldpwdvar = ft_getvar(master->env, "OLDPWD");
    getcwd(cwd, sizeof(cwd)); //! protecten!!!
    if (oldpwdvar)
    {
        free(oldpwdvar->value);
        oldpwdvar->value = ft_getstralloc(cwd); //! protecten!!!
    }
    else
        ft_addvar(&master->env, "OLDPWD", ft_getstralloc(cwd)); //! protecten!!
}

/* sets the current pwd in the enviroment list */

void ft_setpwd(t_master *master)
{
    char cwd[1024];
    t_env *pwdvar;

    pwdvar = ft_getvar(master->env, "PWD");
    getcwd(cwd, sizeof(cwd)); //! protecten!!!
    if (pwdvar)
    {
        free(pwdvar->value);
        pwdvar->value = ft_getstralloc(cwd); //! protecten!!!
    }
    else
        ft_addvar(&master->env, "PWD", ft_getstralloc(cwd)); //! protecten!!
}
