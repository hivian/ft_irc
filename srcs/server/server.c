/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2017/03/06 12:32:35 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void				server_write(t_env *e, int cs)
{
	(void)e;
	(void)cs;
}

static void				server_read(t_env *e, int cs)
{
	int					ret;
	t_user				user;
	char				concat[NICK_SIZE + 20];

	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	memset(concat, 0, NICK_SIZE);
	recv(cs, &user, sizeof(t_user), 0);
	ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[ret] = '\0';
	if (ret <= 0)
	{
		get_time(e);
		printf("\033[31m[%s]\033[0m Client #%d gone away\n", e->strtime, cs);
		strcat(concat, e->fds[cs].user.nickname);
		strcat(concat, " leaved the channel\n");
		send_to_chan(e, concat, e->sock, user);
		clean_fd(cs, e);
		close(cs);
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
	get_time(e);
	if ((cs = accept(e->sock, (struct sockaddr *)&csin, &cslen)) < 0)
		printf("\033[31m[%s]\033[0m Client connection failed", e->strtime);
	recv(cs, &e->fds[cs].user, sizeof(t_user), O_CLOEXEC);
	printf("\033[31m[%s]\033[0m New client #%d from %s:%d\n", e->strtime, cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
	send(cs, "Welcome to this IRC server\n", 27, 0);
	clean_fd(cs, e);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = server_read;
	e->fds[cs].fct_write = server_write;
}
