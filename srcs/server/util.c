/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:49:16 by hivian            #+#    #+#             */
/*   Updated: 2017/03/01 16:49:30 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int				get_fd_from_usr(t_env *e, char *name)
{
	int			i;

	i = 0;
	while (i <= e->max)
	{
		if (!strcmp(e->fds[i].user.nickname, name))
			return (i);
		i++;
	}
	return (-1);
}
