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
	t_env *env = ft_createenvlist(envp);
    t_command *cmd = malloc(sizeof(t_command));
	t_command *cmd2 = malloc(sizeof(t_command));
	t_command *cmd3 = malloc(sizeof(t_command));
	int *pids = malloc(sizeof(int *) * 3);
	master->env = env;
    master->cmds = cmd;
	master->cmds->next = cmd2;
	master->cmds->next->next = cmd3;
	master->pids = pids;
	master->cmds->infiles = NULL;
	master->cmds->outfiles = NULL;
	master->cmds->cmdpath = "/usr/bin/ls";
	master->cmds->next->cmdpath = "/usr/bin/wc";
    char *cmds[] = {"ls", NULL};
	char *cmds2[] = {"wc", "-l", NULL};
	char *cmds3[] = {NULL};
	//char *outfiles[] = {"outfile1.txt", "outfile2.txt", NULL};
	//master->cmds->outfiles = outfiles;
	//master->cmds->append = 1;
	//master->cmds->args = NULL;
	//master->cmds->infiles = NULL;
	//ft_openoutfiles(master, *master->cmds);
    master->cmds->args = cmds;
	master->cmds->next->args = cmds2;
	master->cmds->next->next->args = NULL;
	ft_exec(master);
    //char *infiles[] = {"infisdfsdfle1.txt", "insdfsdffile2.txt", NULL};
    //master->cmds->infiles = infiles;
    //ft_openinfiles(master);
    /* char *test[] = {"export", NULL, "Hellso=3", "Hellso", NULL,
    "SESSION_MANAGER",
    "QT_ACCESSIBILITY",
    "COLORTERM",
    "XDG_CONFIG_DIRS",
    "XDG_MENU_PREFIX",
    "TERM_PROGRAM_VERSION",
    "XDG_CONFIG_DIRS_VSCODE_SNAP_ORIG",
    "GNOME_DESKTOP_SESSION_ID",
    "GDK_BACKEND_VSCODE_SNAP_ORIG",
    "FONTCONFIG_PATH",
    "LANGUAGE",
    "LC_ADDRESS",
    "GIO_MODULE_DIR_VSCODE_SNAP_ORIG",
    "GNOME_SHELL_SESSION_MODE",
    "LC_NAME",
    "SSH_AUTH_SOCK",
    "XDG_DATA_HOME",
    "MEMORY_PRESSURE_WRITE",
    "XMODIFIERS",
    "DESKTOP_SESSION",
    "LC_MONETARY",
    "GTK_MODULES",
    "DBUS_STARTER_BUS_TYPE",
    "PWD",
    "GSETTINGS_SCHEMA_DIR",
    "XDG_SESSION_DESKTOP",
    "LOGNAME",
    "GTK_EXE_PREFIX",
    "XDG_SESSION_TYPE",
    "GPG_AGENT_INFO",
    "SYSTEMD_EXEC_PID",
    "XAUTHORITY",
    "VSCODE_GIT_ASKPASS_NODE",
    "WINDOWPATH",
    "HOME",
    "USERNAME",
    "LC_PAPER",
    "LANG",
    "LS_COLORS",
    "XDG_CURRENT_DESKTOP",
    "MEMORY_PRESSURE_WATCH",
    "VTE_VERSION",
    "GIT_ASKPASS",
    "GNOME_TERMINAL_SCREEN",
    "CHROME_DESKTOP",
    "VSCODE_GIT_ASKPASS_EXTRA_ARGS",
    "GSETTINGS_SCHEMA_DIR_VSCODE_SNAP_ORIG",
    "GTK_IM_MODULE_FILE_VSCODE_SNAP_ORIG",
    "LESSCLOSE",
    "XDG_SESSION_CLASS",
    "LC_IDENTIFICATION",
    "TERM",
    "GTK_PATH",
    "LESSOPEN",
    "USER",
    "GTK_PATH_VSCODE_SNAP_ORIG",
    "VSCODE_GIT_IPC_HANDLE",
    "GNOME_TERMINAL_SERVICE",
    "DISPLAY",
    "SHLVL",
    "LOCPATH",
    "GSM_SKIP_SSH_AGENT_WORKAROUND",
    "LC_TELEPHONE",
    "QT_IM_MODULE",
    "XDG_DATA_HOME_VSCODE_SNAP_ORIG",
    "LC_MEASUREMENT",
    "GTK_EXE_PREFIX_VSCODE_SNAP_ORIG",
    "DBUS_STARTER_ADDRESS",
    "PAPERSIZE",
    "XDG_RUNTIME_DIR",
    "XDG_DATA_DIRS_VSCODE_SNAP_ORIG",
    "DEBUGINFOD_URLS",
    "LC_TIME",
    "FONTCONFIG_FILE",
    "VSCODE_GIT_ASKPASS_MAIN",
    "XDG_DATA_DIRS",
    "GDK_BACKEND",
    "PATH",
    "GDMSESSION",
    "ORIGINAL_XDG_CURRENT_DESKTOP",
    "DBUS_SESSION_BUS_ADDRESS",
    "GTK_IM_MODULE_FILE",
    "LOCPATH_VSCODE_SNAP_ORIG",
    "GIO_MODULE_DIR",
    "LC_NUMERIC",
    "TERM_PROGRAM", "_", "LD_LIBRARY_PATH", "GLIBCPP_FORCE_NEW", "GLIBCXX_FORCE_NEW", "LD_PRELOAD", NULL};
    master->cmds->args = test;
    ft_export(master); */
    //ft_unset(master);
    //ft_addvar(&master->env, ft_getstralloc("Hello"), ft_getstralloc("Hello"));
    //ft_env(*master);
    //ft_pwd();
	ft_freeenv(master);
	free(master);
	free(cmd);
	return (0);
}
