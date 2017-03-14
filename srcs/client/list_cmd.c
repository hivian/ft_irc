/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:06:45 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 15:53:18 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		connect_to(t_env *e, char **input_arr)
{
	close(e->sock);
	free(e->fds);
	ft_strdel(&e->addr);
	clear_list(e->list);
	free(e);
	connect_to_server(ft_arrlen(input_arr), input_arr);
}

void		send_msg(t_env *e, int cs, char **input_arr)
{
	int		maxsize;
	char	*concat_msg;

	maxsize = BUF_SIZE - 6 - NICK_SIZE;
	concat_msg = NULL;
	concat_arr(&concat_msg, input_arr);
	if (strlen(concat_msg) > maxsize)
	{
		memset(e->fds[cs].buf_write, 0, BUF_SIZE);
		strncpy(e->fds[cs].buf_write, concat_msg, maxsize);
	}
	send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	ft_strdel(&concat_msg);
}
