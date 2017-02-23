/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_invalid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 14:18:06 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 12:44:33 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		opt_percent(void)
{
	ft_putchar('%');
	return (1);
}

size_t		opt_invalid(t_format *format)
{
	char	*str;

	str = (char *)malloc(sizeof(str));
	if (!format->flags[0] && !format->width[0] && \
	!format->precision[0] && !format->modifier[0])
	{
		str[0] = format->others[0];
		ft_putstr(str);
		return (ft_strlen(str));
	}
	else
	{
		str = width(format, str);
		str = precision_nbr(format, str);
		if (format->type[0] == '%')
			str = ft_strjoin(str, "%");
		ft_putstr(str);
		return (ft_strlen(str));
	}
}
