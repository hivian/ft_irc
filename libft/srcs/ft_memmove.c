/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:02:05 by hivian            #+#    #+#             */
/*   Updated: 2014/11/05 11:53:10 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char *stmp;

	if (!dst || !src)
		return (NULL);
	stmp = (unsigned char *)malloc(sizeof(*stmp) * n);
	ft_memcpy(stmp, src, n);
	ft_memcpy(dst, stmp, n);
	free(stmp);
	return (dst);
}
