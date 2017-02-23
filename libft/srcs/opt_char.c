/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 10:46:32 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 12:44:09 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		opt_hhd(t_format *format, char hhd)
{
	char	*str;

	str = ft_itoa(hhd);
	str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && hhd == 0)
		return (0);
	else
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
}

size_t		opt_hhu(t_format *format, unsigned char hhu)
{
	char	*str;

	str = ft_uitoa(hhu);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && hhu == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t		opt_hho(t_format *format, unsigned char hho)
{
	char	*str;

	str = ft_uitoa(hho);
	str = ft_conv_base(hho, NULL, "01234567");
	if (!hho)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && hho == 0 && !format->flags[0])
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t		opt_hhx(t_format *format, unsigned char hhx, int maj)
{
	char	*str;
	char	*base;

	str = ft_uitoa(hhx);
	base = (maj == 0 ? "0123456789abcdef" : "0123456789ABCDEF");
	str = ft_conv_base(hhx, NULL, base);
	if (!hhx)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && hhx == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
