#include "minishell.h"

static int ft_checkdir(t_command *cmd);
static int ft_gospecial(t_master *master, char *varpath, t_env *pwd);
static int ft_setpwd(t_master *master);
static int ft_setoldpwd(t_master *master, t_env *pwdvar);

/* builtin cd function like in bash */

int ft_cd(t_master *master)
{
    t_env *pwd;

    pwd = ft_getvar(master->env, "PWD");
    if (master->cmds->args[2])
    {
        ft_printerror(master->cmds->args[0], NULL, TOO_MANY_ARGUMENTS);
        return (1);
    }
    if (!master->cmds->args[1])
        return (ft_gospecial(master, "HOME", pwd));
    if (!ft_strcmp(master->cmds->args[1], "-"))
    {
        if (ft_gospecial(master, "OLDPWD", pwd) == 1)
            return (1);
        ft_pwd();    
        return (0);
    }
        if (ft_checkdir(master->cmds) || chdir(master->cmds->args[1]) == -1)
		return (1);
    ft_setoldpwd(master, pwd);
    ft_setpwd(master);
    return (0);
}

/* changes the current working directory to path in the given variable
saved in the enviroment */

static int ft_gospecial(t_master *master, char *varpath, t_env *pwd)
{
    t_env *envvar;

    envvar = ft_getvar(master->env, varpath);
    if (envvar)
    {
        if(chdir(envvar->value) == -1)
            return (1);
        ft_setoldpwd(master, pwd);
        ft_setpwd(master);
        return (0);
    }
    ft_printerror(master->cmds->args[0], NULL, NULL);
    ft_putstr_fd(varpath, 2);
    ft_putstr_fd(" not set\n", 2);
    return (1);
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

/* sets the cwd in the enviroment on the PWD variable if it exist, if not
PWD var is getting created */

static int ft_setpwd(t_master *master)
{
    t_env *pwdvar;
    char *cwd;

    pwdvar = ft_getvar(master->env, "PWD");
    cwd = getcwd(NULL, 0);
    if (!cwd) //! freen alles!
        return (1);
    if (pwdvar)
    {
        free(pwdvar->value);
        pwdvar->value = cwd;
    }
    else
    {
        ft_addvar(&master->env, ft_getstralloc("PWD"), cwd); //!richtig protecten!
        if (!ft_getvar(master->env, "PWD") || !ft_getvar(master->env, "PWD")->key || !ft_getvar(master->env, "PWD")->value)
        {
            return (1); //! freen alles!!!
        }
    }
    return (0);
}

/* sets the oldpwd path in the eviroment if PWD var exist, if not
nothing will happen */

static int ft_setoldpwd(t_master *master, t_env *pwdvar)
{
    t_env *oldpwdvar;
    char *oldpwdpath;

    oldpwdvar = ft_getvar(master->env, "OLDPWD");
    if (!pwdvar)
        return (0);
    oldpwdpath = ft_getstralloc(pwdvar->value);
    if (!oldpwdpath) //! freen alles!
        return (1);
    if (oldpwdvar)
    {
        free(oldpwdvar->value);
        oldpwdvar->value = oldpwdpath;
    }
    else
    {
        ft_addvar(&master->env, ft_getstralloc("OLDPWD"), oldpwdpath); //!richtig protecten!
        if (!ft_getvar(master->env, "OLDPWD") || !ft_getvar(master->env, "OLDPWD")->key || !ft_getvar(master->env, "OLDPWD")->value)
        {
            return (1); //! freen alles!!!
        }
    }
    return (0);
}
