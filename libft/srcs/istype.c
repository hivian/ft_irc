/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   istype.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 15:07:56 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 15:29:33 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			istype(t_format *format, va_list ap)
{
	if (format->modifier[0] == 'h' && format->modifier[1] == 'h' && \
		(format->type[0] == 'd' || format->type[0] == 'i'))
		return (opt_hhd(format, va_arg(ap, int)));
	else if (format->modifier[0] == 'h' && format->modifier[1] == 'h' && \
		format->type[0] == 'u')
		return (opt_hhu(format, va_arg(ap, unsigned int)));
	else if (format->modifier[0] == 'h' && format->modifier[1] == 'h' && \
		format->type[0] == 'o')
		return (opt_hho(format, va_arg(ap, unsigned int)));
	else if (format->modifier[0] == 'h' && format->modifier[1] == 'h' && \
		format->type[0] == 'x')
		return (opt_hhx(format, va_arg(ap, unsigned int), 0));
	else if (format->modifier[0] == 'h' && format->modifier[1] == 'h' && \
		format->type[0] == 'X')
		return (opt_hhx(format, va_arg(ap, unsigned int), 1));
	else
		return (istype1(format, ap));
}

int			istype1(t_format *format, va_list ap)
{
	if (format->modifier[0] == 'h' && \
		(format->type[0] == 'd' || format->type[0] == 'i'))
		return (opt_hd(format, va_arg(ap, int)));
	else if (format->modifier[0] == 'h' && \
		format->type[0] == 'u')
		return (opt_hu(format, va_arg(ap, unsigned int)));
	else if (format->modifier[0] == 'h' && \
		format->type[0] == 'o')
		return (opt_ho(format, va_arg(ap, unsigned int)));
	else if (format->modifier[0] == 'h' && \
		format->type[0] == 'x')
		return (opt_hx(format, va_arg(ap, unsigned int), 0));
	else if (format->modifier[0] == 'h' && \
		format->type[0] == 'X')
		return (opt_hx(format, va_arg(ap, unsigned int), 1));
	else if (format->modifier[0] == 'l' && format->type[0] == 'c')
		return (opt_wc(format, va_arg(ap, wchar_t)));
	else if (format->modifier[0] == 'l' && format->type[0] == 's')
		return (opt_ws(format, va_arg(ap, wchar_t *)));
	else if (format->type[0] == 'C')
		return (opt_wc(format, va_arg(ap, wchar_t)));
	else if (format->type[0] == 'S')
		return (opt_ws(format, va_arg(ap, wchar_t *)));
	else
		return (istype2(format, ap));
}

int			istype2(t_format *format, va_list ap)
{
	if (format->type[0] == 'D' || ((format->modifier[0] == 'l' || \
		format->modifier[0] == 'j' || format->modifier[0] == 'z') && \
		(format->type[0] == 'd' || format->type[0] == 'i')))
		return (opt_ld(format, va_arg(ap, long int)));
	else if (format->type[0] == 'O' || \
		(format->modifier[0] == 'l' && format->type[0] == 'o') || \
		(format->modifier[0] == 'j' && format->type[0] == 'o') || \
		(format->modifier[0] == 'z' && format->type[0] == 'o'))
		return (opt_lo(format, va_arg(ap, unsigned long int)));
	else if (format->type[0] == 'U' || \
		(format->modifier[0] == 'l' && format->type[0] == 'u') || \
		(format->modifier[0] == 'j' && format->type[0] == 'u') || \
		(format->modifier[0] == 'z' && format->type[0] == 'u'))
		return (opt_lu(format, va_arg(ap, unsigned long int)));
	else if ((format->modifier[0] == 'l' && format->type[0] == 'x') || \
		(format->modifier[0] == 'j' && format->type[0] == 'x') || \
		(format->modifier[0] == 'z' && format->type[0] == 'x'))
		return (opt_lx(format, va_arg(ap, unsigned long int), 0));
	else if ((format->modifier[0] == 'l' && format->type[0] == 'X') || \
		(format->modifier[0] == 'j' && format->type[0] == 'X') || \
		(format->modifier[0] == 'z' && format->type[0] == 'X'))
		return (opt_lx(format, va_arg(ap, unsigned long int), 1));
	else
		return (istype3(format, ap));
}

int			istype3(t_format *format, va_list ap)
{
	if (format->type[0] == 'd' || format->type[0] == 'i')
		return (opt_d(format, va_arg(ap, int)));
	else if (format->type[0] == 's')
		return (opt_s(format, va_arg(ap, char *)));
	else if (format->type[0] == 'c')
		return (opt_c(format, va_arg(ap, int)));
	else if (format->type[0] == 'u')
		return (opt_u(format, va_arg(ap, unsigned int)));
	else if (format->type[0] == 'x')
		return (opt_x(format, va_arg(ap, unsigned int), 0));
	else if (format->type[0] == 'X')
		return (opt_x(format, va_arg(ap, unsigned int), 1));
	else if (format->type[0] == 'o')
		return (opt_o(format, va_arg(ap, unsigned int)));
	else if (format->type[0] == 'p')
		return (opt_p(format, va_arg(ap, void *)));
	else if (format->type[0] == '%' && !format->width[0])
		return (opt_percent());
	else if (format->type[0] == '%' && format->width[0])
		return (opt_invalid(format));
	else if (format->others[0])
		return (opt_invalid(format));
	return (0);
}
