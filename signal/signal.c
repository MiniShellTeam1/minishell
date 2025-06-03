/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/02 13:20:05 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/types.h>

volatile sig_atomic_t g_signal_received = 0;

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	
	sigaction(SIGINT, &sa, NULL);
	
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	g_signal_received = 0;
}

int	check_signal(void)
{
	if (g_signal_received == SIGINT)
	{
		reset_signals();
		return (1);
	}
	return (0);
}