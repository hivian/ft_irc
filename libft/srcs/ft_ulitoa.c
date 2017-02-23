/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 11:25:23 by hivian            #+#    #+#             */
/*   Updated: 2017/01/10 10:44:24 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	int_len(unsigned long int n)
{
	size_t	result;

	result = 0;
	while (n > 0)
	{
		n = n / 10;
		result++;
	}
	return (result);
}

static char		*print_str_ulitoa(char *str, unsigned long int n, size_t len)
{
	while (len > 0)
	{
		str[len - 1] = '0' + n % 10;
		n = n / 10;
		len--;
	}
	return (str);
}

char			*ft_ulitoa(unsigned long int n)
{
	size_t		len;
	char		*str;

	len = int_len(n);
	if (n == 0)
	{
		str = ft_strnew(1);
		*str = '0';
		return (str);
	}
	else
	{
		str = ft_strnew(len);
		return (print_str_ulitoa(str, n, len));
	}
}
