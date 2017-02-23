/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 10:21:07 by hivian            #+#    #+#             */
/*   Updated: 2017/01/10 10:09:39 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		width4(t_format *format, char ***str)
{
	if ((int)ft_atoi(format->width) > ft_atoi_dot(format->precision) && \
	format->precision[0] == '.' && format->type[0] != 'S' && \
	format->type[0] != 's' && !format->others[0])
		**str = ft_strjoin((format->width[0] == '0') ? " " : " ", **str);
	else
		**str = ft_strjoin((format->width[0] == '0') ? "0" : " ", **str);
}

static void		width3(char ***str, int i, int j, char *flag)
{
	j = ft_atoi(**str);
	**str = ft_itoa_ndash(j);
	while ((int)ft_strlen(**str) < i - 1)
		**str = ft_strjoin("0", **str);
	**str = ft_strjoin(flag, **str);
}

static char		*width2(t_format *format, char **str, int i, int j)
{
	while ((int)ft_strlen(*str) < i)
	{
		if (format->flags[0] == '-')
			*str = ft_strjoin(*str, " ");
		else
		{
			if (*str[0] == '-' && format->width[0] == '0')
				width3(&str, i, j, "-");
			else if (*str[0] == '+' && format->width[0] == '0')
				width3(&str, i, j, "+");
			else if (*str[0] == ' ' && format->width[0] == '0')
				width3(&str, i, j, " ");
			else
			{
				width4(format, &str);
				if (format->width[0] == '0' && \
				format->type[0] == 'p' && *str[0] == '0')
				{
					*str = ft_strjoin("0x0", *str);
					return (*str);
				}
			}
		}
	}
	return (*str);
}

char			*width(t_format *format, char *str)
{
	int		i;
	int		j;

	j = 0;
	i = ft_atoi(format->width);
	if (!str[0] && format->type[0] != 'S')
	{
		while ((int)ft_strlen(str) < i - 1)
		{
			if (format->flags[0] == '-')
				str = ft_strjoin(str, " ");
			else
				str = ft_strjoin((format->width[0] == '0') ? "0" : " ", str);
		}
	}
	else
		str = width2(format, &str, i, j);
	return (str);
}
