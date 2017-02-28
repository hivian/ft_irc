/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/02/28 11:03:52 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				client_write(t_env *e, int cs)
{
	if (strcmp(ft_strtrim(e->fds[cs].buf_write), ""))
	{
		get_time(e);
		ft_putstr("\033[36m[");
		ft_putstr(e->strtime);
		ft_putstr("] Me $> \033[0m");
		ft_putstr(e->fds[cs].buf_write);
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
		memset(&e->fds[cs].buf_write, 0, BUF_SIZE);
	}
}

void				client_read(t_env *e, int cs)
{
	int					ret;
	int					i;

	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) < 0)
	{
		close(cs);
		clean_fd(cs, e);
		printf("Client #%d gone away\n", cs);
	}
	e->fds[cs].buf_read[ret] = '\0';
	//printf("len = %d\n", ret);
	if (e->fds[cs].buf_read[ret - 1] == '\n')
	{
		get_time(e);
		ft_putstr("[\033[33m");
		ft_putstr(e->strtime);
		ft_putstr("] Server $> \033[0m");
	}
	ft_putstr(e->fds[cs].buf_read);
}
