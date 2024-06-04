/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:51:33 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/03 17:22:09 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define GREEN "\033[92m"
# define RED "\033[91m"
# define RES "\033[0m"

# include <stdarg.h>
# include <unistd.h>

int				ft_printf(const char *format, ...);
int				ft_myputchar(int c);
int				ft_myputstr(char *s);
int				ft_myputnbr(long n, int base, char param);
int				ft_printptr(unsigned long n, unsigned int base);
int				ft_atoi(char *str);
size_t			ft_strlen(char *str);
unsigned char	*ft_calloc(size_t count, size_t size);

#endif
