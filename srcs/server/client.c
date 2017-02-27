/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2017/02/27 12:46:23 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void				client_write(t_env *e, int cs)
{
	(void)e;
	(void)cs;
}

static void				client_read(t_env *e, int cs)
{
	int					ret;
	int					i;

	ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (ret <= 0)
	{
		close(cs);
		clean_fd(cs, e);
		printf("Client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT && i != cs)
				send(i, e->fds[cs].buf_read, ret, 0);
			i++;
		}
	}
}

void					srv_accept(t_env *e)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			cslen;

	cslen = sizeof(csin);
	if ((cs = accept(e->sock, (struct sockaddr *)&csin, &cslen)) < 0)
		print_error("Connection failed");
		printf("TOTO\n");
	printf("New client #%d from %s:%d, fd = %d\n", cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port), cs);
	clean_fd(cs, e);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
}
