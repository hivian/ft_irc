/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2017/03/02 16:55:59 by hivian           ###   ########.fr       */
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
	t_user				user;

	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	recv(cs, &user, sizeof(t_user), 0);
	ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[ret] = '\0';
	if (ret <= 0)
	{
		close(cs);
		clean_fd(cs, e);
		printf("Client #%d gone away\n", cs);
	}
	else
	{
		if (e->fds[cs].buf_read[0] == '/')
			run_cmd(e, cs, user);
		else
			send_to_chan(e, e->fds[cs].buf_read, cs, user);
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
	recv(cs, &e->fds[cs].user, sizeof(t_user), O_CLOEXEC);
	printf("New client #%d from %s:%d, fd = %d\n", cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port), cs);
	clean_fd(cs, e);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
}
