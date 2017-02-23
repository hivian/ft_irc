/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:42:49 by hivian            #+#    #+#             */
/*   Updated: 2017/01/10 09:56:10 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *ptr;

	if (!size)
		return (NULL);
	ptr = (void *)malloc(size + 1);
	if (ptr)
		ft_bzero(ptr, size + 1);
	return (ptr);
}
