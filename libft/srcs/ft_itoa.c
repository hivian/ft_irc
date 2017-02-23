/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 12:16:53 by hivian            #+#    #+#             */
/*   Updated: 2015/02/14 13:36:58 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_len(int n)
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

static char		*print_str_itoa(char *str, int n, size_t len)
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

char			*ft_itoa(int n)
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
		return ((print_str_itoa(str + 1, n, len) - 1));
	}
	else
	{
		str = ft_strnew(len);
		return (print_str_itoa(str, n, len));
	}
}
