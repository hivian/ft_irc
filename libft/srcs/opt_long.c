/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 11:52:19 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 12:48:21 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			opt_ld(t_format *format, long int ld)
{
	char	*str;

	str = ft_litoa(ld);
	str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && ld == 0)
		return (0);
	else
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
}

size_t			opt_lo(t_format *format, unsigned long int lo)
{
	char	*str;

	str = ft_ulitoa(lo);
	str = ft_conv_base(lo, NULL, "01234567");
	if (!lo)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && lo == 0 && !format->flags[0])
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t			opt_lu(t_format *format, unsigned long int lu)
{
	char	*str;

	str = ft_ulitoa(lu);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && lu == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t			opt_lx(t_format *format, unsigned long int lx, int maj)
{
	char	*str;
	char	*base;

	str = ft_ulitoa(lx);
	base = (maj == 0 ? "0123456789abcdef" : "0123456789ABCDEF");
	str = ft_conv_base(lx, NULL, base);
	if (!lx)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && lx == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
