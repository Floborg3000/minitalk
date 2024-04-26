/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:59 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/26 15:30:22 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 1024


void	stock_str(unsigned char c)
{
    static int              buffer_index = 0;
    static int              current_size = BUFFER_SIZE;
    static unsigned char    *buffer = NULL;
    unsigned char           *new_buffer;

    if (!buffer)
    {
        buffer = malloc(BUFFER_SIZE * sizeof(unsigned char));
        if (!buffer)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return;
        }
    }

    if (buffer_index == current_size - 200) // Si le buffer est plein
    {
        current_size *= 2; // Double la taille du buffer
        new_buffer = malloc(current_size * sizeof(unsigned char)); // Alloue un nouveau buffer
        if (!new_buffer)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return;
        }
        // Copie les données du buffer d'origine vers le nouveau buffer
        for (int i = 0; i < buffer_index; i++)
        {
            new_buffer[i] = buffer[i];
        }
        free(buffer);
		
        buffer = new_buffer; // Met à jour le pointeur du buffer
    }

    buffer[buffer_index++] = c;

    if (c == '\0')
    {
        printf("%s\n", buffer);
        buffer_index = 0;
		//free(new_buffer);
    }
}
	/*static int				buffer_index = 0;
	static unsigned char	*buffer;
	size_t	new_size;
	

	if (!buffer)
		buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (buffer_index == BUFFER_SIZE * 3 / 4)
	{
		new_size = BUFFER_SIZE * 2;
		buffer = realloc(buffer, new_size);
		if (!buffer)
			return ;
		ft_printf("ok realloc\n");
	}
	buffer[buffer_index] = c;
	buffer_index++;	
	if (c == '\0')
	{	
		ft_printf("%s\n", buffer);
		buffer_index = 0;
		free(buffer);
		ft_printf("ok free\n");	
	}
}*/

void	sig_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	current_char;
	static int				i;

	(void)context;
	if (signal == 2)
	{
		ft_printf("Server %d is closing...\n", getpid());
		 exit(EXIT_SUCCESS);
	}
	//current_char |= (signal == SIGUSR1);
	if (signal == SIGUSR1)
		current_char = current_char | 1;
	else if (signal == SIGUSR2)
		current_char = current_char | 0;
		
	i++;
	if (i == 8)
	{
		stock_str(current_char);	
		i = 0;
		current_char = 0;
	}
	else
		current_char = current_char << 1;
	if (signal == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
		
}



int	main(void)
{
	struct sigaction	sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = 0;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = &sig_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	ft_printf("[SERVER] - PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}