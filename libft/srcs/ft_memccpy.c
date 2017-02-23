/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 09:13:19 by hivian            #+#    #+#             */
/*   Updated: 2014/11/05 09:54:48 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dpter;
	unsigned char	*spter;
	unsigned char	convert;
	size_t			i;

	dpter = (unsigned char *)dst;
	spter = (unsigned char *)src;
	convert = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if ((*dpter++ = *spter++) == convert)
			return (dpter);
		i++;
	}
	return (NULL);
}
