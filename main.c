/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:26:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2022/11/15 12:02:07 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main ()
{
	int a = 'f';
	int b = 42;
	char *ptr;
	char *test;
	test = ptr;
	unsigned int  c = -1;

	ft_printf("Meu printf:\n");

	int	percent = ft_printf("%%\n");
	ft_printf("%d\n", percent);

	int chr = ft_printf("%c", 'c');
	ft_printf("%d", chr);

	printf("Printf original:\n");

	int percent_ori = printf("%%\n");
	printf("%d\n", percent_ori);

	int chr_ori = printf("%c", 'c');
	printf("%d", chr_ori);
	return 0;
}
			
