/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/03/02 10:25:37 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				client_write(t_env *e, int cs)
{
	run_cmd(e, cs);
	strcat(e->concat_send, e->fds[cs].buf_write);
	if (e->fds[cs].buf_write[strlen(e->fds[cs].buf_write) - 1] == '\n')
		memset(e->concat_send, 0, BUF_SIZE);
	send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	memset(e->fds[cs].buf_write, 0, BUF_SIZE);
}

static void			print_recv(t_env *e, int cs, char *server, t_user user)
{
	if (strcmp(ft_strtrim(e->fds[cs].buf_read), ""))
	{
		strcat(e->concat_recv, e->fds[cs].buf_read);
		if (e->fds[cs].buf_read[strlen(e->fds[cs].buf_read) - 1] == '\n')
		{
			if (!server)
			{
				server = user.nickname;
				clean_input(e);
				if (user.whisper)
					printf("*\033[33m%s*\033[0m %s", server, e->concat_recv);
				else
					printf("<\033[33m%s>\033[0m %s", server, e->concat_recv);
			}
			else
				printf("\033[31m%s\033[0m %s", server, e->concat_recv);
			memset(e->concat_recv, 0, BUF_SIZE);
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
	{
		server = "==";
		clean_input(e);
	}
	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) < 0)
	{
		close(cs);
		clean_fd(cs, e);
		printf("Recv error\n");
	}
	e->fds[cs].buf_read[ret] = '\0';
	print_recv(e, cs, server, user);
}
