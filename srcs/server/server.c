/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 10:36:06 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void				server_write(t_env *e, int cs)
{
	send(cs, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	memset(e->fds[cs].buf_write, 0, BUF_SIZE);
}

static void				server_read(t_env *e, int cs)
{
	t_user				user;
	char				concat[NICK_SIZE + 14];

	memset(concat, 0, NICK_SIZE);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	if ((e->ret_recv = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) <= 0)
	{
		strcpy(concat, e->fds[cs].user.nickname);
		clean_fd(cs, e);
		close(cs);
		get_time(e);
		printf("\033[31m[%s]\033[0m Client #%d gone away\n", e->strtime, cs);
		strcat(concat, " disconnected\n");
		send_to_chan(e, concat, MSG_INFO, cs);
	}
	else
	{
		e->fds[cs].buf_read[e->ret_recv] = '\0';
		if (e->fds[cs].buf_read[0] == '/')
			run_cmd(e, cs, user);
		else
			send_to_chan(e, e->fds[cs].buf_read, MSG_STD, cs);
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
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = server_read;
	e->fds[cs].fct_write = server_write;
	strcpy(e->fds[cs].user.channel, CHAN_GEN);
	strcpy(e->fds[cs].user.nickname, "Guest");
	strcat(e->fds[cs].user.nickname, ft_itoa(cs));
	send(cs, e->fds[cs].user.nickname, NICK_SIZE, 0);
	printf("\033[31m[%s]\033[0m New client #%d from %s:%d\n", e->strtime, cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	printf("\033[31m[%s]\033[0m %s joined %s\n", e->strtime, \
		e->fds[cs].user.nickname, e->fds[cs].user.channel);
	memset(concat, 0, NICK_SIZE + 9 + CHAN_SIZE);
	strcpy(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	e->max++;
	send_to_chan(e, concat, MSG_INFO, cs);
}
