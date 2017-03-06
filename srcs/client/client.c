/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/03/06 16:38:17 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				client_write(t_env *e, int cs)
{
	if (e->fds[cs].buf_write[0] == '/')
		run_cmd(e, cs);
	else
	{
		send(e->sock, &e->fds[cs].user, sizeof(t_user), 0);
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	}
	memset(e->fds[cs].buf_write, 0, BUF_SIZE);
}

static void			print_recv(t_env *e, int cs, char *server, t_user user)
{
	if (strcmp(ft_strtrim(e->fds[cs].buf_read), ""))
	{
		e->concat_recv = ft_strjoin(e->concat_recv, e->fds[cs].buf_read);
		clean_input(e);
		if (e->fds[cs].buf_read[strlen(e->fds[cs].buf_read) - 1] == '\n')
		{
			if (!server)
			{
				server = user.nickname;
				if (user.whisper)
					printf("*\033[33m%s*\033[0m %s", server, e->concat_recv);
				else
					printf("<\033[33m%s>\033[0m %s", server, e->concat_recv);
			}
			else
			{
				if (e->cmd_who)
					server = "";
				printf("\033[31m%s\033[0m%s", server, e->concat_recv);
				e->cmd_who = false;
			}
			ft_strdel(&e->concat_recv);
		}
	}
}

void				client_read(t_env *e, int cs)
{
	int					ret;
	int					i;
	char				*server;
	t_user				user;

	server = NULL;
	recv(cs, &user, sizeof(t_user), 0);
	if (!strcmp(user.nickname, ""))
		server = "== ";
	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) < 0)
	{
		close(cs);
		clean_fd(cs, e);
		printf("Recv error\n");
	}
	e->fds[cs].buf_read[ret] = '\0';
	if (!strcmp(e->fds[e->sock].buf_read, "Nickname is already in use\n"))
	{
		memset(e->fds[e->sock].user.nickname, 0, NICK_SIZE);
		strcpy(e->fds[e->sock].user.nickname, e->nick_backup);
	}
	print_recv(e, cs, server, user);
}
