/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 08:25:59 by hivian            #+#    #+#             */
/*   Updated: 2015/02/05 12:41:53 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *dst;

	if (!s)
		return (NULL);
	dst = ft_strnew(len);
	if (!dst)
		return (NULL);
	dst = ft_strncpy(dst, &s[start], len);
	dst[len] = '\0';
	return (dst);
}
