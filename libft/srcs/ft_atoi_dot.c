/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_dot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 12:01:27 by hivian            #+#    #+#             */
/*   Updated: 2015/01/18 11:17:45 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi_dot(const char *str)
{
	int		sign;
	int		nb;

	sign = 1;
	nb = 0;
	while (*str == ' ' || *str == '\n' || *str == '\v'
		|| *str == '\t' || *str == '\r' || *str == '\f' || *str == '.')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (sign * nb);
}
