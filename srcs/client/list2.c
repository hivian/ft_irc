/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 15:27:41 by hivian            #+#    #+#             */
/*   Updated: 2017/03/09 15:31:30 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		free_node(t_node *node)
{
	ft_strdel(&node->nickname);
	free(node);
	node = NULL;
}

void			del_node(t_slist *list, char *data)
{
	t_node		*tmp;

	tmp = list->head;
	if (tmp == NULL)
		return ;
	if (tmp && tmp->next == NULL)
	{
		list->head = NULL;
		free_node(tmp);
	}
	else if (!strcmp(tmp->nickname, data))
	{
		list->head = tmp->next;
		tmp->next = tmp->next->next;
		free_node(tmp);
	}
	else
	{
		while (tmp->next && strcmp(tmp->next->nickname, data))
			tmp = tmp->next;
		free_node(tmp->next);
		tmp->next = tmp->next->next;
	}
}

int				is_ignored(t_slist *list, char *data)
{
	t_node		*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (!strcmp(tmp->nickname, data))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
