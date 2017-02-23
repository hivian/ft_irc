/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 12:08:52 by hivian            #+#    #+#             */
/*   Updated: 2015/01/10 12:11:02 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		int_len(long int n)
{
	size_t result;

	result = 0;
	while (n < 0)
	{
		n = n / 10;
		result++;
	}
	while (n > 0)
	{
		n = n / 10;
		result++;
	}
	return (result);
}

static char			*print_str_litoa(char *str, long int n, size_t len)
{
	if (n < 0)
	{
		while (len > 0)
		{
			str[len - 1] = '0' - n % 10;
			n = n / 10;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			str[len - 1] = '0' + n % 10;
			n = n / 10;
			len--;
		}
	}
	return (str);
}

char				*ft_litoa(long int n)
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
	else if (n < 0)
	{
		str = ft_strnew(len + 1);
		*str = '-';
		return ((print_str_litoa(str + 1, n, len) - 1));
	}
	else
	{
		str = ft_strnew(len);
		return (print_str_litoa(str, n, len));
	}
}
