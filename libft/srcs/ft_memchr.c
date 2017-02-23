/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:41:44 by hivian            #+#    #+#             */
/*   Updated: 2014/11/05 14:33:02 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*stmp;
	size_t			i;

	if (!s || !n)
		return (NULL);
	stmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (stmp[i] == (unsigned char)c)
			return ((void *)(stmp + i));
		i++;
	}
	return (NULL);
}
