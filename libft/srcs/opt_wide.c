/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_wide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 15:57:13 by hivian            #+#    #+#             */
/*   Updated: 2015/01/18 10:56:24 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			opt_wc(t_format *format, wchar_t wc)
{
	char	*str;
	char	buff[5];

	ft_bzero(buff, 5);
	str = (char *)malloc(sizeof(wchar_t) + 1);
	str = ft_set_unicode(buff, wc);
	str = width(format, str);
	if (!str[0])
		write(1, str, 1);
	else
		ft_putstr(str);
	if (!str[0])
		return (ft_strlen(str) + 1);
	return (ft_strlen(str));
}

static void		prec_or_not(t_format *format, char **str, wchar_t *ws, int i)
{
	char	buff[5];
	int		j;
	int		k;

	j = -1;
	ft_bzero(buff, 5);
	k = ft_atoi_dot(format->precision);
	while (ws[++i])
	{
		if (format->precision[0] != '.')
			*str = ft_strjoin(*str, ft_set_unicode(buff, ws[i]));
		if (format->type[0] == 'S' && format->precision[0] == '.')
		{
			if ((int)ft_strlen(ft_set_unicode(buff, ws[i])) <= k)
			{
				*str = ft_strjoin(*str, ft_set_unicode(buff, ws[++j]));
				k = k - 4 + 1;
			}
		}
	}
}

size_t			opt_ws(t_format *format, wchar_t *ws)
{
	char	*str;
	int		i;

	i = -1;
	if (ws == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	str = (char *)malloc(sizeof(wchar_t *) + 1);
	prec_or_not(format, &str, ws, i);
	str = width(format, str);
	ft_putstr(str);
	return (ft_strlen(str));
}
