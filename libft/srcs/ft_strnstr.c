/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 08:29:17 by hivian            #+#    #+#             */
/*   Updated: 2014/11/09 12:04:50 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	if (s2[0] == '\0' || s2 == NULL)
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[j])
			j++;
		else
			j = 0;
		if (s2[j] == '\0' && i < n)
			return ((char *)s1 + (i - (j - 1)));
		i++;
	}
	return (NULL);
}
