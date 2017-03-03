/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:49:16 by hivian            #+#    #+#             */
/*   Updated: 2017/03/03 16:58:37 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void				get_time(t_env *e)
{
	time_t			timer;
	struct tm		*tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(e->strtime, DATE_SIZE, "%Y-%m-%d %H:%M:%S", tm_info);
}

int					duplicate_user(t_env *e, int cs, char *name)
{
	int				i;

	i = 0;
	while (i <= e->max)
	{
		if (!strcmp(e->fds[i].user.nickname, name) && i != cs)
			return (1);
		i++;
	}
	return (0);
}

int					get_fd_from_usr(t_env *e, char *name)
{
	int				i;

	i = 0;
	while (i <= e->max)
	{
		if (!strcmp(e->fds[i].user.nickname, name))
			return (i);
		i++;
	}
	return (-1);
}
