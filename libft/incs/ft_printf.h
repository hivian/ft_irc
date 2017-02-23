/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 10:13:15 by hivian            #+#    #+#             */
/*   Updated: 2015/01/18 12:22:29 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <wchar.h>

typedef struct		s_var
{
	int				ret;
	int				i;
	int				counter;
}					t_var;

typedef struct		s_format
{
	char			*flags;
	char			*width;
	char			*precision;
	char			*modifier;
	char			*type;
	char			*others;
}					t_format;

typedef struct		s_counter
{
	int				flags;
	int				width;
	int				precision;
	int				modifier;
	int				type;
	int				others;
}					t_counter;

int					ft_printf(const char *str, ...);
int					istype(t_format *format, va_list ap);
int					istype1(t_format *format, va_list ap);
int					istype2(t_format *format, va_list ap);
int					istype3(t_format *format, va_list ap);
int					count_format(char *s, t_format **format, t_counter *c);
size_t				opt_d(t_format *format, int n);
size_t				opt_s(t_format *format, char *str);
size_t				opt_c(t_format *format, char c);
size_t				opt_u(t_format *format, unsigned int u);
size_t				opt_x(t_format *format, unsigned int x, int maj);
size_t				opt_o(t_format *format, unsigned int o);
size_t				opt_p(t_format *format, void *p);
size_t				opt_ld(t_format *format, long int ld);
size_t				opt_lo(t_format *format, unsigned long int lo);
size_t				opt_lu(t_format *format, unsigned long int lu);
size_t				opt_lx(t_format *format, unsigned long int lx, int maj);
size_t				opt_wc(t_format *format, wchar_t wc);
size_t				opt_ws(t_format *format, wchar_t *ws);
size_t				opt_hd(t_format *format, short hhd);
size_t				opt_hu(t_format *format, unsigned short hhu);
size_t				opt_ho(t_format *format, unsigned short hho);
size_t				opt_hx(t_format *format, unsigned short hhx, int maj);
size_t				opt_hhd(t_format *format, char hhd);
size_t				opt_hhu(t_format *format, unsigned char hhu);
size_t				opt_hho(t_format *format, unsigned char hho);
size_t				opt_hhx(t_format *format, unsigned char hhx, int maj);
size_t				opt_invalid(t_format *format);
size_t				opt_percent(void);
char				*width(t_format *format, char *str);
char				*flags(t_format *format, char *str);
char				*modifier(t_format *format, char *str);
char				*precision_nbr(t_format *format, char *str);

void				ft_putwchar(wchar_t c);
void				ft_putwstr(const wchar_t *s);
size_t				ft_strwlen(const wchar_t *s);
char				*ft_set_unicode(char *buff, wchar_t wc);

#endif
