/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2017/03/15 12:28:24 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void				server_write(t_env *e, int cs)
{
	send(cs, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	//printf("write = %s", e->fds[cs].buf_write);
	memset(e->fds[cs].buf_write, 0, BUF_SIZE);
}

static void				handle_msg(t_env *e, int cs, char *buf)
{
	if (buf[0] == '/')
		run_cmd(e, cs, buf);
	else
		send_to_chan(e, buf, MSG_STD, cs);
}

static void				ring_buffer(t_env *e, int cs, char *msg)
{
	char				buf[BUF_SIZE + 1];
	int					i;
	static int			j = -1;

	i = 0;
	if (j == -1)
	{
		memset(buf, 0, BUF_SIZE + 1);
		j = 0;
	}
	while (msg[i])
	{
		if (j >= BUF_SIZE - 12 - NICK_SIZE){
			printf("HERE\n");
			j = 0;
		}
		buf[j++] = msg[i++];
	}
	//buf[j] = '\0';
	printf("RING BUFF = %s\n", buf);
	if (ft_strchr(buf, '\n'))
	{
		handle_msg(e, cs, buf);
		memset(buf, 0, BUF_SIZE + 1);
		j = 0;
	}
}

static void				server_read(t_env *e, int cs)
{
	char				concat[NICK_SIZE + 14];

	memset(concat, 0, NICK_SIZE);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	if ((e->ret_recv = recv(cs, e->fds[cs].buf_read, BUF_SIZE - 12 - NICK_SIZE, 0)) <= 0)
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
		printf("BUFF = %s\n", e->fds[cs].buf_read);
		e->fds[cs].buf_read[e->ret_recv] = '\0';
		ring_buffer(e, cs, e->fds[cs].buf_read);
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
