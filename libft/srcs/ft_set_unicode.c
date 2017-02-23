/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_unicode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 08:53:55 by hivian            #+#    #+#             */
/*   Updated: 2015/01/18 12:19:15 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_set_unicode(char *buff, wchar_t wc)
{
	ft_bzero(buff, ft_strlen(buff));
	if (wc < 0x80)
		buff[0] = ((wc >> 0) & 0x7F) | 0x00;
	else if (wc < 0x0800)
	{
		buff[0] = ((wc >> 6) & 0x1F) | 0xC0;
		buff[1] = ((wc >> 0) & 0x3F) | 0x80;
	}
	else if (wc < 0x010000)
	{
		buff[0] = ((wc >> 12) & 0x0F) | 0xE0;
		buff[1] = ((wc >> 6) & 0x3F) | 0x80;
		buff[2] = ((wc >> 0) & 0x3F) | 0x80;
	}
	else if (wc < 0x110000)
	{
		buff[0] = ((wc >> 18) & 0x07) | 0xF0;
		buff[1] = ((wc >> 12) & 0x3F) | 0x80;
		buff[2] = ((wc >> 6) & 0x3F) | 0x80;
		buff[3] = ((wc >> 0) & 0x3F) | 0x80;
	}
	if (wc < 0x80 || wc < 0x0800 || wc < 0x010000 || wc < 0x110000)
		return (buff);
	return (NULL);
}
