/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_pxxo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 09:08:59 by hivian            #+#    #+#             */
/*   Updated: 2015/01/16 09:41:34 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		opt_x(t_format *format, unsigned int x, int maj)
{
	char	*str;
	char	*base;

	str = ft_uitoa(x);
	base = (maj == 0 ? "0123456789abcdef" : "0123456789ABCDEF");
	str = ft_conv_base(x, NULL, base);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (!x)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	if (format->precision[0] == '.' && x == 0)
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t		opt_o(t_format *format, unsigned int o)
{
	char	*str;

	str = ft_uitoa(o);
	str = ft_conv_base(o, NULL, "01234567");
	if (!o)
		str = ft_strjoin(str, "0");
	else
		str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	if (format->precision[0] == '.' && o == 0 && !format->flags[0])
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t		opt_p(t_format *format, void *p)
{
	char				*str;
	unsigned long int	n;

	str = ft_strdup("");
	n = (char *)p - (char *)0;
	str = ft_ulitoa(n);
	str = ft_conv_base(n, NULL, "0123456789abcdef");
	str = precision_nbr(format, str);
	if (str[0] != 0 || format->width[0] != '0')
		str = ft_strjoin("0x", str);
	if (!n && format->precision[0] != '.')
		str = ft_strjoin(str, "0");
	str = width(format, str);
	ft_putstr(str);
	return (ft_strlen(str));
}
