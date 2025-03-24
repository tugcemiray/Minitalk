/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 03:53:24 by tukaraca          #+#    #+#             */
/*   Updated: 2025/03/24 04:01:56 by tukaraca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sig_handler(int sig_num, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;

	(void)context;
	if (sig_num == SIGUSR1)
		c = c | (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	print_pid(int pid)
{
	char	c;

	if (pid > 9)
		print_pid(pid / 10);
	c = pid % 10 + 48;
	write(1, &c, 1);
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = getpid();
	write(1, "Server PID: ", 13);
	print_pid(pid);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
