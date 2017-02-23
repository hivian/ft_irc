/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 16:00:57 by hivian            #+#    #+#             */
/*   Updated: 2017/01/10 09:56:16 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void	*dup;

	if (!(dup = ft_memalloc(size)))
		return (NULL);
	ft_memcpy(dup, ptr, size);
	ft_memdel(&ptr);
	return (dup);
}
