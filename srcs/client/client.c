/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/02/28 17:09:47 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				client_write(t_env *e, int cs)
{
	run_cmd(e, cs);
	strcat(e->concat_send, e->fds[cs].buf_write);
	if (e->fds[cs].buf_write[strlen(e->fds[cs].buf_write) - 1] == '\n')
	{
		//get_time(e);
		//printf("\b\b\b   \b\b\b\033[36m[%s] Me #%d $>\033[0m %s", \
		e->strtime, cs, e->concat_send);
		memset(e->concat_send, 0, BUF_SIZE);
	}
	send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	memset(e->fds[cs].buf_write, 0, BUF_SIZE);
}

void				client_read(t_env *e, int cs)
{
	int					ret;
	int					i;

	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) < 0)
	{
		close(cs);
		clean_fd(cs, e);
		printf("Recv error\n");
	}
	e->fds[cs].buf_read[ret] = '\0';
	if (strcmp(ft_strtrim(e->fds[cs].buf_read), ""))
	{
		strcat(e->concat_recv, e->fds[cs].buf_read);
		if (e->fds[cs].buf_read[ret - 1] == '\n')
		{
			get_time(e);
			clean_buffer(e, "Clienttttttttttttttt");
			printf("\033[33mClient $>\033[0m %s", e->concat_recv);
			memset(e->concat_recv, 0, BUF_SIZE);
		}
	}
}
