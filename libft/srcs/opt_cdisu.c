/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_cdisu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 15:01:54 by hivian            #+#    #+#             */
/*   Updated: 2017/01/11 16:16:30 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

size_t			opt_d(t_format *format, int n)
{
	char	*str;

	str = ft_itoa(n);
	str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && n == 0 && format->width[0] != '0')
		return (0);
	else
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
}

size_t			opt_s(t_format *format, char *str)
{
	char	*str2;

	str2 = "0";
	if (str == NULL && format->width[0] == '0')
	{
		str2 = width(format, str2);
		ft_putstr(str2);
		return (ft_strlen(str2));
	}
	else if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	str = width(format, str);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t			opt_c(t_format *format, char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) + 1);
	str[0] = c;
	str = width(format, str);
	if (c == 0)
	{
		write(1, str, ft_atoi(format->width) + ft_strlen(format->flags));
		return (ft_strlen(str) + 1);
	}
	else
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
}

size_t			opt_u(t_format *format, unsigned int u)
{
	char	*str;

	str = ft_uitoa(u);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && u == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
