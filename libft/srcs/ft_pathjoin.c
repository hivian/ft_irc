/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 12:26:26 by hivian            #+#    #+#             */
/*   Updated: 2015/01/26 15:15:48 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char *path, char *bs, char *str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, bs);
	tmp2 = ft_strjoin(tmp, str);
	free(tmp);
	return (tmp2);
}
