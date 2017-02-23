/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 08:43:01 by hivian            #+#    #+#             */
/*   Updated: 2014/11/14 11:18:21 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (alst != NULL)
	{
		if (*alst != NULL)
		{
			(*del)((**alst).content, (**alst).content_size);
			free(*alst);
		}
		*alst = NULL;
	}
}
