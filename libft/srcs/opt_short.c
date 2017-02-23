/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_short.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 16:03:21 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 13:35:29 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		opt_hd(t_format *format, short hd)
{
	char	*str;

	str = ft_itoa(hd);
	str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && hd == 0)
		return (0);
	else
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
}

size_t		opt_hu(t_format *format, unsigned short hu)
{
	char	*str;

	str = ft_uitoa(hu);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && hu == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t		opt_ho(t_format *format, unsigned short ho)
{
	char	*str;

	str = ft_uitoa(ho);
	str = ft_conv_base(ho, NULL, "01234567");
	if (!ho)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && ho == 0 && !format->flags[0])
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t		opt_hx(t_format *format, unsigned short hx, int maj)
{
	char	*str;
	char	*base;

	str = ft_uitoa(hx);
	base = (maj == 0 ? "0123456789abcdef" : "0123456789ABCDEF");
	str = ft_conv_base(hx, NULL, base);
	if (!hx)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && hx == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
