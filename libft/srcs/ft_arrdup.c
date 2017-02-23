/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 16:47:21 by hivian            #+#    #+#             */
/*   Updated: 2015/02/14 16:00:10 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_arrdup(char **array)
{
	char	**ret;
	int		i;

	if (!(ret = (char **)malloc(sizeof(char *) * (ft_arrlen(array) + 1))))
		return (NULL);
	i = 0;
	while (array[i])
	{
		ret[i] = ft_strdup(array[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
