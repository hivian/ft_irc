/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/02/27 12:25:16 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				client_write(t_env *e, int cs)
{
	char			buf[BUF_SIZE + 1];
	int				ret;
	int				i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT && i != cs)
			send(i, e->fds[cs].buf_write, ret, 0);
		i++;
	}
}

void				client_read(t_env *e, int cs)
{
	int					ret;
	int					i;

	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) < 0)
	{
		close(cs);
		clean_fd(cs, e);
		printf("Client #%d gone away\n", cs);
	}
	e->fds[cs].buf_read[ret] = '\0';
	printf("Client:Message Received From Server - %s\n", e->fds[cs].buf_read);
	/*else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT && i != cs)
				send(i, e->fds[cs].buf_read, ret, 0);
			i++;
		}
	}*/
}
