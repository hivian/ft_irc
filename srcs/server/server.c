/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2017/03/17 11:06:13 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void				server_write(t_env *e, int cs)
{
	send(cs, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	memset(e->fds[cs].buf_write, 0, BUF_SIZE + 1);
}

static void				server_read(t_env *e, int cs)
{
	char				concat[NICK_SIZE + 15];

	memset(concat, 0, NICK_SIZE + 15);
	if ((e->ret_recv = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) <= 0)
	{
		strcpy(concat, e->fds[cs].user.nickname);
		strcat(concat, " disconnected\n");
		send_to_chan(e, concat, MSG_INFO, cs);
		clean_fd(cs, e);
		close(cs);
		get_time(e);
		printf("\033[31m[%s]\033[0m Client #%d gone away\n", e->strtime, cs);
	}
	else
	{
		e->fds[cs].buf_read[e->ret_recv] = '\0';
		ring_buffer_read(e, cs, e->fds[cs].buf_read);
		memset(e->fds[cs].buf_read, 0, BUF_SIZE + 1);
	}
}

static void				init_client(t_env *e, int cs)
{
	char				*cs_to_str;

	cs_to_str = ft_itoa(cs);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = server_read;
	e->fds[cs].fct_write = server_write;
	strcpy(e->fds[cs].user.channel, CHAN_GEN);
	strcpy(e->fds[cs].user.nickname, "Guest");
	strcat(e->fds[cs].user.nickname, cs_to_str);
	ft_strdel(&cs_to_str);
}

void					srv_accept(t_env *e)
{
	int					cs;
	char				concat[NICK_SIZE + 9 + CHAN_SIZE];

	e->cslen = sizeof(e->csin);
	get_time(e);
	if ((cs = accept(e->sock, (struct sockaddr *)&e->csin, &e->cslen)) < 0)
		printf("\033[31m[%s]\033[0m Client connection failed", e->strtime);
	init_client(e, cs);
	send(cs, e->fds[cs].user.nickname, NICK_SIZE, 0);
	printf("\033[31m[%s]\033[0m New client #%d from %s:%d\n", e->strtime, cs,
		inet_ntoa(e->csin.sin_addr), ntohs(e->csin.sin_port));
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
