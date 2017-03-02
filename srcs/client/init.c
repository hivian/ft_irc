/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 09:37:25 by hivian            #+#    #+#             */
/*   Updated: 2017/03/02 16:54:43 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				clean_fd(int i, t_env *e)
{
	e->fds[i].type = FD_FREE;
	e->fds[i].fct_read = NULL;
	e->fds[i].fct_write = NULL;
}

void				check_fd(t_env *e)
{
	if (e->ret > 0)
	{
		if (FD_ISSET(e->sock, &e->fd_read))
			e->fds[e->sock].fct_read(e, e->sock);
		if (FD_ISSET(e->sock, &e->fd_write))
			e->fds[e->sock].fct_write(e, e->sock);
		if (FD_ISSET(STDIN_FILENO, &e->fd_read))
		{
			memset(e->fds[e->sock].buf_write, 0, BUF_SIZE);
			int ret = read(0, e->fds[e->sock].buf_write, BUF_SIZE + 1);
		}
    }
}

void				init_env(t_env *e)
{
	if (!(e->fds = (t_fd*)malloc(sizeof(*e->fds))))
		print_error("malloc: failed");
	clean_fd(e->sock, e);
	memset(e->concat_send, 0, BUF_SIZE);
	memset(e->concat_recv, 0, BUF_SIZE);
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
