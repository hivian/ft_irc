/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 09:37:25 by hivian            #+#    #+#             */
/*   Updated: 2017/02/27 15:24:43 by hivian           ###   ########.fr       */
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
	int				i;

	i = 0;
	while (i < e->maxfd && e->ret > 0)
	{
		if (FD_ISSET(i, &e->fd_read))
		{
			printf("READ\n");
			e->fds[i].fct_read(e, i);
		}
		printf("i = %d\n", i);
		if (FD_ISSET(i, &e->fd_write))
		{
			//e->fds[i].fct_write(e, i);
			send(e->sock, e->fds[i].buf_write, strlen(e->fds[i].buf_write), 0);
            memset(&e->fds[i].buf_write, 0, BUF_SIZE);
		}
		if(FD_ISSET(STDIN_FILENO, &e->fd_read))
		{
			read(0, e->fds[i].buf_write, BUF_SIZE);
		}
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->ret--;
		i++;
    }
}

void				init_env(t_env *e)
{
	int				i;
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) < 0)
		print_error("getrlimit: failed");
	e->maxfd = rlp.rlim_cur;
	if (!(e->fds = (t_fd*)malloc(sizeof(*e->fds) * e->maxfd)))
		print_error("malloc: failed");
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(i, e);
		i++;
	}
}

void				init_fd(t_env *e)
{
	int				i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(STDIN_FILENO, &e->fd_write);
	FD_SET(STDIN_FILENO, &e->fd_read);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			//if (strlen(e->fds[i].buf_write) > 0)
				FD_SET(i, &e->fd_write);
			e->max = MAX(e->max, i);
		}
		i++;
	}
}
