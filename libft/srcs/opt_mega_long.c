/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_mega_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 09:17:59 by hivian            #+#    #+#             */
/*   Updated: 2015/01/14 09:26:50 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		opt_lld(t_format *format, long long int n)
{
	char		*str;

	str = ft_llitoa(n);
	str = flags(format, str);
	str = precision_nbr(format, str);
	str = width(format, str);
	ft_putstr(str);
	return (ft_strlen(str));
}
