/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 08:58:07 by hivian            #+#    #+#             */
/*   Updated: 2014/11/05 09:08:47 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dpter;
	const char	*spter;

	dpter = dst;
	spter = src;
	while (n > 0)
	{
		*dpter++ = *spter++;
		n--;
	}
	return (dst);
}
