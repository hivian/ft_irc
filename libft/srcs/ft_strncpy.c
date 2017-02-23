/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:29:16 by hivian            #+#    #+#             */
/*   Updated: 2014/11/10 08:54:38 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char *tmp;

	tmp = dst;
	while (n > 0 && *src != '\0')
	{
		*tmp++ = *src++;
		--n;
	}
	while (n > 0)
	{
		*tmp++ = '\0';
		--n;
	}
	return (dst);
}
