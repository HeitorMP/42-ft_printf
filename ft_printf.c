/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 04:32:40 by hmaciel-          #+#    #+#             */
/*   Updated: 2022/11/14 19:08:01 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

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

static void	ft_putchar_fd(char c, int fd)
{	
	write(fd, &c, 1);
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


int	ft_ptr_len(unsigned long long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static int put_pointer(unsigned long long np)
{
	char	base[] = "0123456789abcdef";
	unsigned long long len;

	len = ft_ptr_len(np);
	if (np >= 16)
	{
		put_pointer(np / 16);
		put_pointer(np % 16);
	}
	else
		write(1, &base[np], 1);
	return (len);
}

static int	put_hex(long int np, char x)
{
	char	base[] = "0123456789abcdef";
	static int digits;

	if (np < 0)
		np =  (4294967295 - (np * -1)) + 1;

	if (x == 'X')
		ft_strupcase(base);
	if (np >= 16)
	{
		put_hex(np / 16, x);
		put_hex(np % 16, x);
		digits++;
	}
	else
		write(1, &base[np], 1);
	return (digits - 1);
}

static void ft_putunsigned(unsigned int n)
{
	ft_putnbr_fd(n, 1);
}

static int ft_check_format(char next, va_list args)
{
	int len;

	len = 0;
	if (next == '%')
	{
		write (1, "%", 1);
		len = 1;
	}
	else if (next == 'c')
	{
		char char_to_print;
		char_to_print = va_arg(args, int);
        write(1, &char_to_print, 1);
		len = 1;
	}
	else if (next == 's')
	{
		char	*str;
		str = va_arg(args, char*);
		if (!str)
		{
			len = 6;
			write(1, "(null)", 6);
		}
		else
		{
			ft_putstr_fd(str, 1);
			len = (ft_strlen(str));
		}
	}
	else if (next == 'd' || next == 'i')
	{
		int	nbr;
		nbr = va_arg(args, int);
		len = ft_get_digits(nbr);
		ft_putnbr_fd(nbr, 1);
	}
	else if (next == 'x' || next == 'X')
	{
		int	ret;
		ret = va_arg(args, long long int);
		return(put_hex(ret, next));
	}
	else if (next == 'p')
	{
		long long int ret;
		ret = va_arg(args, long long int);
		if (!ret)
		{
			write(1, "(nil)", 5);
			len = 5;
		}
		else
		{
			write(1, "0x", 2);
			len = put_pointer(ret) + 2;
		}
	}
	else if (next == 'u')
	{
		unsigned int ret;
		ret = va_arg(args, unsigned int);
		if (!ret)
		{
			len = 1;
		}
		else 
		{
			len = ft_get_digits(ret);
			ft_putunsigned(ret);
		}
	}
	return (len - 2);
}

int	ft_printf(const char *str, ...)
{
	va_list argp;
	va_start(argp, str);
	int len;

	len = ft_strlen((str));
	while (*str != '\0')
	{
		if(*str == '%')
		{
			str++;
			len += ft_check_format(*str, argp);
		}
		else 
			write(1, &*str, 1);
		str++;
	}
	return (len);
}
/*
int main ()
{
	int a = 'f';
	int b = 42;
	char *ptr;
	char *test;

	test = ptr;
	//unsigned int  c = -1;

	ft_printf("Meu printf:\n");
	int d = ft_printf("Hexa: %x\n", 123456);
	ft_printf("hexa size: %d\n", d);
	int e = ft_printf("String: %s\n", "teste");
	ft_printf("String size: %i\n", e);
	int f = ft_printf("Char: %c\n", 'c');
	ft_printf("Char size: %d\n", f);
	int g = ft_printf("Unsinged int: %u\n", -1);
	ft_printf("UnInt Size: %d\n", g);
	int h = ft_printf("Int: %d\n", b);
	ft_printf("int Size: %d\n", h);
	int q = ft_printf("A pointer at %p points to %p\n", &test, &ptr);
	ft_printf("%d\n", q);
	int i = ft_printf("Pointer: %p\n" ,(void *)0xdeadc0de );
	ft_printf("Pointer Size: %d\n", i);

//	int z = ft_printf("\n%ces\\te\n %s\n %d - %x - %X - %p\n %i - %x - %X - %p\n %i - %d - %u", 't', "teste", b, b, b, &b, a, a, a, &a, c, c, c);
//	ft_printf("\n%i", z);
	ft_printf("\n------------------------------\n");
	ft_printf("Printf original:\n");
	int j = printf("Hexa: %x\n", 123456);
	printf("hexa size: %d\n", j);
	int k = printf("String: %s\n", "teste");
	printf("String size: %i\n", k);
	int l = printf("Char: %c\n", 'c');
	printf("Char size: %d\n", l);
	int m = printf("Unsinged int: %u\n", -1);
	printf("UnInt size: %d\n", m);
	int n = printf("Int: %d\n", b);
	printf("Int size: %d\n", n);
	int p = printf("A pointer at %p points to %p\n", &test, &ptr);
	printf("%d\n", p);
	int o = printf("Pointer: %p\n",(void *)0xdeadc0de );
	printf("Pointer size: %d\n", o);
	return 0;
}*/
