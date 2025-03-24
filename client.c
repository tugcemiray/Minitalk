/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 03:53:30 by tukaraca          #+#    #+#             */
/*   Updated: 2025/03/24 04:01:02 by tukaraca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ack_rcvd = 0;

void	ack_control(int sig)
{
	if (sig == SIGUSR1)
		g_ack_rcvd = 1;
	else
		exit(EXIT_FAILURE);
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (sign * result);
}

void	send_char(int pid, char c)
{
	struct sigaction	sa;
	int					i;

	i = 0;
	sa.sa_handler = ack_control;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	while (i < 7)
	{
		g_ack_rcvd = 0;
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_ack_rcvd == 0)
			pause();
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (kill(pid, 0) == -1 || pid > 4194304 || pid <= -1)
		{
			write(1, "Error\n", 6);
			return (0);
		}
		while (argv[2][i])
		{
			if (pid == 0)
				return (EXIT_FAILURE);
			send_char(pid, argv[2][i]);
			i++;
		}
		write(1, "Message received\n ", 18);
		send_char(pid, '\n');
	}
	else if (argc != 3)
		write(1, "The number of arguments must be three!", 39);
	return (0);
}
