/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:40:43 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/04 14:53:37 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	g_pid;

static void	send_len(pid_t pid, size_t len)
{
	size_t	size;
	size_t	bit;

	size = sizeof(size_t) * 8;
	while (size > 0)
	{
		bit = (len >> (size - 1)) & 1;
		if (bit == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		size--;
		usleep(50);
	}
}

static void	send_bits(pid_t pid, char *str)
{
	int				i;
	unsigned char	bit;

	while (*str)
	{
		i = 8;
		while (--i >= 0)
		{
			bit = *str >> i;
			if (bit % 2 == 0)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
		str++;
	}
	i = 8;
	while (--i >= 0)
	{
		kill(pid, SIGUSR2);
		usleep(50);
	}
	while (1)
		usleep(10);
}

static void	handle_signal(int signum)
{
	if (signum == SIGUSR1)
	{
		ft_printf(GREEN "\nMessage received by %d\n\n" RES, g_pid);
		exit (0);
	}
	else if (signum == SIGUSR2)
	{
		ft_printf(RED "\nTransmission CANCELED\n\n" RES);
		exit (0);
	}
}

static void	handle_sigint(int signum)
{
	int	i;

	if (signum == SIGINT)
	{
		i = 0;
		while (i++ <= 16)
		{
			kill(g_pid, SIGUSR1);
			usleep(500);
		}
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa_usr;
	struct sigaction	sa_int;

	pid = ft_atoi(argv[1]);
	g_pid = pid;
	if (argc == 3 && pid >= 2)
	{
		sa_usr.sa_handler = handle_signal;
		sa_int.sa_handler = handle_sigint;
		sigemptyset(&sa_usr.sa_mask);
		sigemptyset(&sa_int.sa_mask);
		sigaddset(&sa_int.sa_mask, SIGINT);
		sigaddset(&sa_usr.sa_mask, SIGUSR1);
		sigaddset(&sa_usr.sa_mask, SIGUSR2);
		if (sigaction(SIGUSR1, &sa_usr, NULL) == -1 || sigaction(SIGUSR2, \
		&sa_usr, NULL) == -1 || sigaction(SIGINT, &sa_int, NULL) == -1)
			return (1);
		send_len(pid, ft_strlen(argv[2]));
		send_bits(pid, argv[2]);
	}
	else
		ft_printf(RED "\nError\nInvalid argument\n" RES);
	return (0);
}
