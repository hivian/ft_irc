/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 08:15:48 by hivian            #+#    #+#             */
/*   Updated: 2015/01/18 11:13:30 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*precision_nbr(t_format *format, char *str)
{
	int		i;
	int		j;

	i = ft_atoi_dot(format->precision);
	if (str[0] != '-')
	{
		while ((int)ft_strlen(str) < i)
		{
			if (ft_strchr(format->precision, '.'))
				str = ft_strjoin("0", str);
		}
	}
	else if (str[0] == '-' && format->precision[0] == '.')
	{
		j = ft_atoi(str);
		str = ft_itoa_ndash(j);
		while ((int)ft_strlen(str) < i)
		{
			if (ft_strchr(format->precision, '.'))
				str = ft_strjoin("0", str);
		}
		str = ft_strjoin("-", str);
	}
	return (str);
}
