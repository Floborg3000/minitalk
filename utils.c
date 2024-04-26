/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:31:31 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/26 15:52:27 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

unsigned char	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	if ((count * size) > 0)
	{
		while (i < (count * size))
		{
			ptr[i] = 0;
			i++;
		}
	}
	return (ptr);
}

unsigned char	*ft_realloc(unsigned char *ptr, size_t size)
{
	unsigned char	*new_ptr;
	size_t			old_size;
	
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
    {
        old_size = sizeof(ptr);
        memcpy(new_ptr, ptr, old	_size);
    }
	free(ptr);
	return (new_ptr);
}