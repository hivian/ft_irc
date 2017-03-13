/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/13 12:24:07 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			send_to_chan(t_env *e, char *message, int msg_type, char *chan)
{
	int			i;

	i = 0;
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && \
		!strcmp(e->fds[i].user.channel, chan))
		{
			if (msg_type == MSG_ERR)
				strcpy(e->fds[i].buf_write, "== ");
			strcat(e->fds[i].buf_write, message);
		}
		i++;
	}
}

void			run_cmd(t_env *e, int cs, t_user user)
{
	char		**input_arr;

	input_arr = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (!strcmp(input_arr[0], "/nick") && ft_arrlen(input_arr) == 2)
		change_nick(e, cs, input_arr, user);
	if (!strcmp(input_arr[0], "/msg") && ft_arrlen(input_arr) > 2)
		send_msg(e, input_arr, cs);
	else if (!strcmp(input_arr[0], "/join") && ft_arrlen(input_arr) == 2)
		join_chan(e, cs, input_arr, user);
	else if (!strcmp(input_arr[0], "/leave") && ft_arrlen(input_arr) == 2)
		leave_chan(e, cs, input_arr, user);
	else if (!strcmp(input_arr[0], "/who\n") && ft_arrlen(input_arr) == 1)
		who(e, cs, user);
	ft_arrdel(input_arr);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	e->fds[cs].user.whisper = false;
}
