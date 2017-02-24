/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 09:37:25 by hivian            #+#    #+#             */
/*   Updated: 2017/02/24 10:37:38 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void				check_fd(t_env *e)
{
	int				i;

	i = 0;
	while (i < e->maxfd && e->ret > 0)
	{
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);
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
		e->fds[i].type = FD_FREE;
	    e->fds[i].fct_read = NULL;
	    e->fds[i].fct_write = NULL;
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
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (strlen(e->fds[i].buf_write) > 0)
				FD_SET(i, &e->fd_write);
			e->max = MAX(e->max, i);
		}
		i++;
	}
}
