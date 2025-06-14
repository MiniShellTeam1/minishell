/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 16:54:36 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_errorcode(t_master *master)
{
	master->errorcode = 0;
}

t_master	*init_master(void)
{
	t_master	*master;

	master = malloc(sizeof(t_master));
	if (!master)
		return (NULL);
	master->cmds = NULL;
	master->env = NULL;
	master->pids = NULL;
	master->errorcode = 0;
	return (master);
}

void	free_master(t_master *master)
{
	t_env	*tmp;

	if (!master)
		return ;
	free_command(master->cmds);
	while (master->env)
	{
		tmp = master->env;
		master->env = master->env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	if (master->pids)
		free(master->pids);
	free(master);
}

static void	process_command_line(t_master *master, char *line)
{
	t_token_list	*tokens;

	if (*line)
		add_history(line);
	tokens = lexer(line);
	if (!tokens)
	{
		master->errorcode = 2;
		return ;
	}
	debug_shell_state(tokens, NULL, NULL, "After Lexing");
	master->cmds = parser(tokens, master);
	if (!master->cmds)
	{
		free_token_list(tokens);
		master->errorcode = 2;
		return ;
	}
	debug_shell_state(NULL, master->cmds, NULL, "After Parsing");
	handle_heredoc(master->cmds, master);
	set_errorcode(master);
	debug_shell_state(NULL, NULL, master, "Before Executor");
	ft_exec(master);
	free_command(master->cmds);
	master->cmds = NULL;
	free_token_list(tokens);
}

int	main(int argc, char *argv[], char **env)
{
	t_master	*master;
	char		*line;

	(void)argc;
	(void)argv;
	master = init_master();
	if (!master)
		return (1);
	master->env = ft_createenvlist(env);
	if (!master->env)
		ft_freeandexit(master, 1);
	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (check_signal())
		{
			free(line);
			continue ;
		}
		process_command_line(master, line);
		free(line);
	}
	free_master(master);
	return (master->errorcode);
}
