/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 09:37:25 by hivian            #+#    #+#             */
/*   Updated: 2017/03/09 12:09:15 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				clean_fd(int i, t_env *e)
{
	e->fds[i].type = FD_FREE;
	e->fds[i].fct_read = NULL;
	e->fds[i].fct_write = NULL;
	memset(e->fds[i].buf_write, 0, BUF_SIZE);
	memset(e->fds[i].buf_read, 0, BUF_SIZE);
	memset(e->fds[i].user.channel, 0, CHAN_SIZE);
	memset(e->fds[i].user.nickname, 0, NICK_SIZE);
	e->fds[i].user.whisper = false;
}

void				check_fd(t_env *e)
{
	char			*line;

	line = NULL;
	if (e->ret > 0)
	{
		if (FD_ISSET(e->sock, &e->fd_read))
			e->fds[e->sock].fct_read(e, e->sock);
		if (FD_ISSET(e->sock, &e->fd_write))
			e->fds[e->sock].fct_write(e, e->sock);
		if (FD_ISSET(STDIN_FILENO, &e->fd_read) && get_next_line(0, &line) == 1)
		{
			strncpy(e->fds[e->sock].buf_write, line, BUF_SIZE - 2);
			e->fds[e->sock].buf_write[strlen(e->fds[e->sock].buf_write)] = '\n';
			ft_strdel(&line);
		}
	}
}

void				init_env(t_env *e)
{
	if (!(e->fds = (t_fd*)malloc(sizeof(*e->fds))))
		print_error("malloc: failed");
	memset(e->concat_recv, 0, BUF_SIZE);
	e->maxfd = 0;
	e->max = 0;
	e->sock = 0;
	e->ret = 0;
	e->id_to_str = NULL;
	e->get_id = 0;
	memset(e->nick_backup, 0, NICK_SIZE);
	memset(e->nick_ignored, 0, NICK_SIZE);
	memset(e->concat_recv, 0, BUF_SIZE);
	clean_fd(e->sock, e);
}

void				init_fd(t_env *e)
{
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(e->sock, &e->fd_read);
	if (strlen(e->fds[e->sock].buf_write) > 0)
		FD_SET(e->sock, &e->fd_write);
	FD_SET(STDIN_FILENO, &e->fd_read);
}
