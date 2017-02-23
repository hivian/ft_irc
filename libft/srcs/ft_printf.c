/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 11:28:22 by hivian            #+#    #+#             */
/*   Updated: 2017/01/11 16:06:54 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_var		*init_var(void)
{
	t_var		*var;

	var = (t_var *)malloc(sizeof(t_var));
	var->ret = 0;
	var->i = 0;
	var->counter = 0;
	return (var);
}

static t_counter	*init_counter(void)
{
	t_counter	*c;

	c = (t_counter *)malloc(sizeof(t_counter));
	c->flags = 0;
	c->width = 0;
	c->precision = 0;
	c->modifier = 0;
	c->type = 0;
	c->others = 0;
	return (c);
}

static void			check_opts(char *s, t_counter *c, va_list ap, t_var *v)
{
	t_format	*format;

	if (s[v->i] == '%')
	{
		v->counter = count_format(&s[v->i], &format, c);
		v->ret += istype(format, ap);
		if (!c->flags && c->width && format->precision[0] == '.' && !c->type)
			v->i = v->i + v->counter + 1;
		else if (c->flags && !c->width && !c->modifier && !c->type)
			v->i = v->i + v->counter + 1;
		else if ((c->flags || c->width || c->precision || c->modifier))
			v->i = v->i + v->counter;
		else if (s[v->i++] == '\0')
			v->i = v->i + v->counter + 1;
		else
			v->i++;
		free(format);
	}
}

int					ft_printf(const char *str, ...)
{
	va_list		ap;
	t_var		*v;
	char		*s;
	t_counter	*c;

	v = init_var();
	c = init_counter();
	va_start(ap, str);
	s = ft_strdup(str);
	while (s[v->i])
	{
		while (s[v->i] != '%' && s[v->i])
		{
			ft_putchar(s[v->i++]);
			v->ret++;
		}
		check_opts(s, c, ap, v);
	}
	va_end(ap);
	free(c);
	free(s);
	return (v->ret);
}
