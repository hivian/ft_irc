/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:22:11 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 12:01:19 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_format		*init_format(char *s, t_counter *c)
{
	t_format	*size;

	size = (t_format *)malloc(sizeof(t_format));
	size->flags = ft_strsub(s, 0, c->flags);
	size->width = ft_strsub(s + c->flags, 0, c->width);
	size->precision = ft_strsub(s + c->flags + c->width, 0, c->precision);
	size->modifier = ft_strsub(s + c->flags + \
		c->width + c->precision, 0, c->modifier);
	size->type = ft_strsub(s + c->flags + c->width + \
		c->precision + c->modifier, 0, c->type);
	size->others = ft_strsub(s + c->flags + c->width + \
		c->precision + c->modifier + c->type, 0, c->others);
	return (size);
}

static void			count_format3(char *s, t_counter *c, int i, char *no_type)
{
	while (ft_strchr("jhzlL", s[i]))
	{
		if (s[i + 1] == 'l' || s[i + 1] == 'h')
		{
			c->modifier = 2;
			i = i + 2;
		}
		else
		{
			c->modifier = 1;
			i++;
		}
	}
	if (ft_strchr("sSpdDioOuUxXcC%", s[i]))
	{
		c->type = 1;
		c->type++;
		i++;
	}
	if (ft_strchr(no_type, s[i]))
	{
		c->others++;
		i++;
	}
}

void				count_format2(char *s, t_counter *c, int i, char *no_type)
{
	while (ft_isdigit(s[i]) || s[i] == '*')
	{
		if (ft_isdigit(s[i + 1]) && (ft_strchr(no_type, s[i + 2])))
		{
			c->width = 3;
			i = i + 3;
		}
		else
		{
			c->width++;
			i++;
		}
	}
	while (s[i] == '.' || ft_isdigit(s[i]))
	{
		if (s[i] == '.')
			c->precision = 1;
		else
			c->precision++;
		i++;
	}
	count_format3(s, c, i, no_type);
}

int					count_format(char *s, t_format **format, t_counter *c)
{
	char		*no_type;
	int			i;

	i = 0;
	no_type = "!""$&'(),/:;<=>?@ABEFGHIJKMNPQRTVWYZ[\\]^_`abefgmnqrtvwyz{|}~";
	if (s[i] == '%')
	{
		i++;
		while (ft_strchr(" #-+", s[i]))
		{
			c->flags = 1;
			if (ft_strchr(" #-+", s[i + 1]))
			{
				c->flags = 2;
				i = i + 2;
			}
			else
				i++;
		}
		count_format2(s, c, i, no_type);
	}
	*format = init_format(s + 1, c);
	return (c->flags + c->width + c->precision + c->modifier + c->type);
}
