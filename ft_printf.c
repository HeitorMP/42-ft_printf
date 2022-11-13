/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 04:32:40 by hmaciel-          #+#    #+#             */
/*   Updated: 2022/11/13 13:24:23 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_fd(char c, int fd)
{	
	write(fd, &c, 1);
}

static void	ft_putnbr_fd(long int np, int fd)
{
	long int	number;

	number = np;
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

static void	ft_putstr_fd(char *s, int fd)
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

static char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= ('a' - 'A');
		i++;
	}
	return (str);
}

static void	put_hex(long int np, char x)
{
	char	base[] = "0123456789abcdef";
	
	if (np < 0)
		np = 4294967295 - (np * -1) + 1;
	if (x == 'X')
		ft_strupcase(base);
	if (np > 16)
	{
		put_hex(np / 16, x);
		put_hex(np % 16, x);
	}
	else
		write(1, &base[np], 1);
}

static void ft_putunsigned(unsigned int n)
{
	ft_putnbr_fd(n, 1);
}

static void ft_check_format(char next, va_list args)
{
	if (next == '%')
		write (1, "%", 1);
	else if (next == 'c')
	{
		char char_to_print;
		char_to_print = va_arg(args, int);
        write(1, &char_to_print, 1);
	}
	else if (next == 's')
	{
		char	*str;
		str = va_arg(args, char*);
		ft_putstr_fd(str, 1);
	}
	else if (next == 'd' || next == 'i')
	{
		int	nbr;
		nbr = va_arg(args, int);
		ft_putnbr_fd(nbr, 1);		
	}
	else if (next == 'x' || next == 'X')
	{
		int	ret;
		ret = va_arg(args, int);
		put_hex(ret, next);
	}
	else if (next == 'p')
	{
		long int ret;
		ret = va_arg(args, long int);
		write(1, "0x", 2);
		put_hex(ret, 'x');
	}
	else if (next == 'u')
	{
		int ret;
		ret = va_arg(args, int);
		ft_putunsigned(ret);
	}
}

static size_t   ft_printf_strlen(const char *s)
{
    int len;

    len = 0;
	if (!s)
		return (len);
    while (*s != '\0')
    {
        if (*s == '%')
        {
          if (*s++ == '\0')
          {
            len++;
            break ;
          }
        }
        len++;
        s++;        
    }
    return (len);
}


int	ft_printf(const char *str, ...)
{
	va_list argp;
	va_start(argp, str);
	int	ret = ft_printf_strlen(str);

	while (*str != '\0')
	{
		if(*str == '%')
		{
			str++;
			ft_check_format(*str, argp);
		}
		else 
		{
			write(1, &*str, 1);
		}
		str++;
	}
	return (ret);
}
/*
int main ()
{
	int a = 'f';
	int b = 42;
	unsigned int  c = -1;

	ft_printf("Meu printf:\n");
	ft_printf("%ces\\te\n %s\n %d - %x - %X - %p\n %i - %x - %X - %p\n %i - %d - %u", 't', "teste", b, b, b, &b, a, a, a, &a, c, c, c);
	ft_printf("\n------------------------------\n");
	ft_printf("Printf original:");
	printf("\n%ces\\te\n %s\n %d - %x - %X - %p\n %i - %x - %X - %p\n %i - %d - %u", 't', "teste", b, b, b, &b, a, a, a, &a, c, c, c);
	return 0;
}*/
