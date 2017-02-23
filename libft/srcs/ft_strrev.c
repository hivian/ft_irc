/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 09:50:58 by hivian            #+#    #+#             */
/*   Updated: 2015/01/10 09:53:25 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrev(const char *s)
{
	char		*str;
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * len + 1);
	while (len)
		str[i++] = s[--len];
	str[i] = '\0';
	return (str);
}
