/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:40:43 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/26 15:22:26 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int g_count;

void	send_bits(unsigned char c, pid_t pid)
{
	int				i;
	unsigned char	bit;

	i = 8;
	bit = c;
	while (--i >= 0)
	{
		bit = c >> i;
		if (bit % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(600);
	}
}

void sigusr1_handler(int signum) 
{
	if (signum == SIGUSR1)
	{
		ft_printf("Received bit 1 %d\n", g_count); //SIGURS1
		g_count++;
	}
}

void sigusr2_handler(int signum)
{
	if (signum == SIGUSR2)
	{
		ft_printf("Received bit 0 %d\n", g_count); //SIGURS2
		g_count++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	struct sigaction sa_usr1, sa_usr2;
	
	if (argc != 3)
	{
		ft_printf("Error\n");
		exit (EXIT_FAILURE);
	}
	i = 0;
    sa_usr1.sa_handler = sigusr1_handler;
    sa_usr2.sa_handler = sigusr2_handler;
    sigemptyset(&sa_usr1.sa_mask);
    sigemptyset(&sa_usr2.sa_mask);
    sa_usr1.sa_flags = 0;
    sa_usr2.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa_usr1, NULL) == -1 || sigaction(SIGUSR2, &sa_usr2, NULL) == -1)
		return (1);
	pid = ft_atoi(argv[1]);
	ft_printf("%d\n", pid);
	while (argv[2][i])
	{
		send_bits(argv[2][i], pid);
		i++;
	}
	send_bits('\0', pid);
	ft_printf("%d\n", g_count);
	return (0);
}