/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:13:25 by hivian            #+#    #+#             */
/*   Updated: 2014/11/06 15:36:01 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t n;
	size_t i;
	size_t j;
	size_t res;

	i = 0;
	j = 0;
	while (i < size && dst[i])
		i++;
	res = i + ft_strlen(src);
	n = size - i - 1;
	if (i != size)
	{
		while (src[j] && j < n)
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (res);
}
