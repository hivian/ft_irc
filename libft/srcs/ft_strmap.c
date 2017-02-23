/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 17:36:58 by hivian            #+#    #+#             */
/*   Updated: 2014/11/14 12:55:26 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	len;
	char	*str;

	if (s && f)
	{
		i = 0;
		len = ft_strlen(s);
		str = ft_strnew(len);
		str = ft_strcpy(str, s);
		while (str[i] != '\0')
		{
			str[i] = f(str[i]);
			i++;
		}
		return (str);
	}
	return (NULL);
}
