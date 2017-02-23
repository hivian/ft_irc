/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 09:59:50 by hivian            #+#    #+#             */
/*   Updated: 2015/01/17 17:02:46 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*join_str(char *s, char c, size_t len)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * len + 2);
	ft_strcpy(new, s);
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}

char			*ft_conv_base(unsigned long int n, char *str, char *base)
{
	int		i;

	if (!str)
	{
		if ((str = (char *)malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
	}
	if (!n)
		return (ft_strrev(str));
	else
	{
		i = n % ft_strlen(base);
		return (ft_conv_base(n / ft_strlen(base), \
		join_str(str, base[i], ft_strlen(str)), base));
	}
}
