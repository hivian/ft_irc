/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 08:29:13 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 09:21:54 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flags2(t_format *format, char **str, int i)
{
	if (format->flags[0] == ' ' && (format->type[0] == 'd' || \
		format->type[0] == 'i' || format->type[0] == 'D') && i >= 0 && \
		format->flags[1] != '+')
		*str = ft_strjoin(" ", *str);
	else if (format->flags[0] == '#' && (format->type[0] == 'o' || \
		format->type[0] == 'O'))
		*str = ft_strjoin("0", *str);
	else if (format->flags[0] == '#' && format->type[0] == 'x')
		*str = ft_strjoin("0x", *str);
	else if (format->flags[0] == '#' && format->type[0] == 'X')
		*str = ft_strjoin("0X", *str);
}

char			*flags(t_format *format, char *str)
{
	long long int		i;
	int					j;
	int					k;

	k = 0;
	j = ft_strlen(format->flags);
	i = ft_atoi(str);
	while (k < j)
	{
		if (ft_strchr("+", format->flags[k]) && (format->type[0] == 'd' || \
		format->type[0] == 'i' || format->type[0] == 'D') && i >= 0)
		{
			str = ft_strjoin("+", str);
			return (str);
		}
		else
			flags2(format, &str, i);
		k++;
	}
	return (str);
}
