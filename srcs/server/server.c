/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2017/03/07 13:10:36 by hivian           ###   ########.fr       */
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
	char				concat[NICK_SIZE + 14];

	memset(concat, 0, NICK_SIZE);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	recv(cs, &user, sizeof(t_user), 0);
	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) <= 0)
	{
		strcat(concat, e->fds[cs].user.nickname);
		strcpy(user.channel, e->fds[cs].user.channel);
		clean_fd(cs, e);
		close(cs);
		get_time(e);
		printf("\033[31m[%s]\033[0m Client #%d gone away\n", e->strtime, cs);
		strcat(concat, " disconnected\n");
		send_to_chan(e, concat, e->sock, user.channel);
	}
	else
	{
		e->fds[cs].buf_read[ret] = '\0';
		if (e->fds[cs].buf_read[0] == '/')
			run_cmd(e, cs, user);
		else
			send_to_chan(e, e->fds[cs].buf_read, cs, user.channel);
	}
}

void					srv_accept(t_env *e)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			cslen;
	char				concat[NICK_SIZE + 9 + CHAN_SIZE];

	cslen = sizeof(csin);
	get_time(e);
	if ((cs = accept(e->sock, (struct sockaddr *)&csin, &cslen)) < 0)
		printf("\033[31m[%s]\033[0m Client connection failed", e->strtime);
	send(cs, &cs, sizeof(cs), 0);
	recv(cs, &e->fds[cs].user, sizeof(t_user), O_CLOEXEC);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = server_read;
	e->fds[cs].fct_write = server_write;
	printf("\033[31m[%s]\033[0m New client #%d from %s:%d\n", e->strtime, cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	printf("\033[31m[%s]\033[0m %s joined %s\n", e->strtime, \
		e->fds[cs].user.nickname, e->fds[cs].user.channel);
	memset(concat, 0, NICK_SIZE + 9 + CHAN_SIZE);
	strcat(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	e->max++;
	send_to_chan(e, concat, e->sock, e->fds[cs].user.channel);
}
