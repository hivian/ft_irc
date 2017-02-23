/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 09:15:52 by hivian            #+#    #+#             */
/*   Updated: 2014/11/22 13:49:52 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlst;
	t_list *begin;

	if (!lst || !f)
		return (NULL);
	begin = (*f)(lst);
	if (lst->next)
		lst = lst->next;
	newlst = begin;
	while (lst != NULL)
	{
		newlst->next = (*f)(lst);
		lst = lst->next;
		newlst = newlst->next;
	}
	return (begin);
}
