/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2022/11/15 13:38:50 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_digits(long long int nb)
{
	int	digits;

	digits = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
nb *= -1;
digits = 1;
	}
	while (nb > 0)
	{
		digits++;
		nb /= 10;
	}
	return (digits);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

void	ft_putchar_fd(char c, int fd)
{	
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long int n, int fd)
{
	long int	number;

	number = n;
	if (number < 0)
	{
		ft_putchar_fd('-', fd);
		number *= -1;
	}
	if (number < 10)
		ft_putchar_fd(number + '0', fd);
	else
	{
		ft_putnbr_fd(number / 10, fd);
		ft_putchar_fd(number % 10 + '0', fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (s)
	{	
		while (s[index] != '\0')
		{
			write(fd, &s[index], 1);
			index++;
		}
	}
}
