#include "minishell.h"

void ft_unset(t_master *master)
{
    int x;
    t_env *tmp;

    x = 1;
    tmp = master->env;
    while (master->cmds->args[x])
    {
        ft_delvar(&master->env, master->cmds->args[x]);
        x++;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_master master;
    master.env = ft_createenvlist(envp);
    t_command *test1 = malloc(sizeof(t_command) * 1);
    master.cmds = test1;

    char *env[] = {
		"unset",
		"LANGUAGE",
		"USER",
		"XDG_SESSION_TYPE",
		"SHLVL",
		"HOME",
		"OLDPWD",
		"DESKTOP_SESSION",
		"GTK_MODULES",
		"XDG_SEAT_PATH",
		"SYSTEMD_EXEC_PID",
		"DBUS_SESSION_BUS_ADDRESS",
		"DBUS_STARTER_BUS_TYPE",
		"LIBVIRT_DEFAULT_URI",
		"COLORTERM",
		"GTK_IM_MODULE",
		"LOGNAME",
		"_",
		"XDG_SESSION_CLASS",
		"TERM",
		"FT_HOOK_PATHNAME",
		"RUSTUP_HOME",
		"GNOME_DESKTOP_SESSION_ID",
		"PATH",
		"SESSION_MANAGER",
		"GDM_LANG",
		"GNOME_TERMINAL_SCREEN",
		"XDG_MENU_PREFIX",
		"XDG_SESSION_PATH",
		"XDG_RUNTIME_DIR",
		"DISPLAY",
		"LANG",
		"XDG_CURRENT_DESKTOP",
		"XDG_SESSION_DESKTOP",
		"GNOME_TERMINAL_SERVICE",
		"XMODIFIERS",
		"XAUTHORITY",
		"SSH_AUTH_SOCK",
		"XDG_GREETER_DATA_DIR",
		"SSH_AGENT_LAUNCHER",
		"KRB5CCNAME",
		"SHELL",
		"QT_ACCESSIBILITY",
		"GDMSESSION",
		"FT_HOOK_NAME",
		"DOCKER_HOST",
		"GPG_AGENT_INFO",
		"QT_IM_MODULE",
		"PWD",
		"XDG_CONFIG_DIRS",
		"XDG_DATA_DIRS",
		"DBUS_STARTER_ADDRESS",
		"CARGO_HOME",
		"VTE_VERSION",
		"CHROME_DESKTOP",
		"ORIGINAL_XDG_CURRENT_DESKTOP",
		"GDK_BACKEND",
		"TERM_PROGRAM",
		"TERM_PROGRAM_VERSION",
		"GIT_ASKPASS",
		"VSCODE_GIT_ASKPASS_NODE",
		"VSCODE_GIT_ASKPASS_EXTRA_ARGS",
		"VSCODE_GIT_ASKPASS_MAIN",
		"VSCODE_GIT_IPC_HANDLE",
		"VSCODE_INJECTION",
		"ZDOTDIR",
		"USER_ZDOTDIR",
		NULL
	};
    master.cmds->args = env;
    ft_unset(&master);
    //printf("%p\n", master.env);
	//printf("%s", master.env->key);
    //ft_env(master);
	ft_addvar(&master.env, "TEST", "TEST");
	char *test[] = {"env", NULL};
	master.cmds->args = test;
	ft_env(master);
/* 	while (master.env)
	{
		ft_putstr_fd(master.env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(master.env->value, 1);
		ft_putstr_fd("\n", 1);
		master.env = master.env->next;
	} */
} 