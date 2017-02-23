/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ndash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 15:48:23 by hivian            #+#    #+#             */
/*   Updated: 2015/01/18 10:53:18 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		int_len(int n)
{
	size_t		result;

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

char		*print_str_itoa_ndash(char *str, int n, size_t len)
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

char		*ft_itoa_ndash(int n)
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
		return (print_str_itoa_ndash(str, n, len));
	}
}
