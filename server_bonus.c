/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:59 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/04 10:53:27 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	g_total_bits;

static void	stock_str(unsigned char c, int len, siginfo_t *inf)
{
	static int				buffer_index = 0;
	static unsigned char	*buf = NULL;

	if (g_total_bits == (sizeof(size_t) * 8) && !buf)
		buf = ft_calloc(len + 1, sizeof(char));
	buf[buffer_index] = c;
	buffer_index++;
	if (c == 0 || c == 255)
	{
		if (c == 0)
		{
			ft_printf("%s\n"GREEN"Message from %d DONE\n"RES, buf, inf->si_pid);
			kill(inf->si_pid, SIGUSR1);
		}
		else if (c == 255)
		{
			ft_printf(RED"\n\nMessage from %d CANCELED\n\n"RES, inf->si_pid);
			kill(inf->si_pid, SIGUSR2);
		}
		buffer_index = 0;
		free(buf);
		buf = NULL;
		g_total_bits = 0;
		len = 0;
	}
}

static void	handle_sigint(void)
{
	ft_printf(GREEN "\nServer %d is closing...\n" RES, getpid());
	exit(EXIT_SUCCESS);
}

static void	handle_signal_len(int signal, int *len)
{
	if (signal == SIGUSR1)
		*len = (*len << 1) | 1;
	else if (signal == SIGUSR2)
		*len = (*len << 1);
	g_total_bits++;
}

static void	sig_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	current_char = 0;
	static int				i = 0;
	static int				len = 0;

	(void)context;
	(void)info;
	if (signal == SIGINT)
		handle_sigint();
	else if (g_total_bits < (sizeof(size_t) * 8))
		handle_signal_len(signal, &len);
	else
	{
		if (signal == SIGUSR1)
			current_char = (current_char << 1) | 1;
		else if (signal == SIGUSR2)
			current_char = (current_char << 1);
		if (++i == 8)
		{
			stock_str(current_char, len, info);
			i = 0;
			current_char = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = &sig_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1 || \
	sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	ft_printf(GREEN "\n[SERVER] - PID: %d\n" RES, getpid());
	while (1)
		pause();
	return (0);
}
