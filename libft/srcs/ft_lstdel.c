/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 08:48:12 by hivian            #+#    #+#             */
/*   Updated: 2014/11/14 11:08:01 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next_lst;
	t_list	*temp;

	if (alst != NULL)
	{
		next_lst = *alst;
		while (next_lst != NULL)
		{
			if (del != NULL)
				(*del)(next_lst->content, (*next_lst).content_size);
			temp = next_lst->next;
			free(next_lst);
			next_lst = temp;
		}
		*alst = NULL;
	}
}
