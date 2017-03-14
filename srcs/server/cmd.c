/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 16:04:22 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			send_to_chan(t_env *e, char *message, int msg_type, int cs)
{
	int			i;

	i = 0;
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && \
		!strcmp(e->fds[i].user.channel, e->fds[cs].user.channel))
		{
			if (msg_type == MSG_INFO)
			{
				strcpy(e->fds[i].buf_write, "\033[31m== \033[0m");
				strcat(e->fds[i].buf_write, message);
			}
			else if (i != cs)
			{
				strcpy(e->fds[i].buf_write, "\033[33m<");
				strcat(e->fds[i].buf_write, e->fds[cs].user.nickname);
				strcat(e->fds[i].buf_write, ">\033[0m ");
				strcat(e->fds[i].buf_write, message);
			}
		}
		i++;
	}
}

void			run_cmd(t_env *e, int cs)
{
	char		**input_arr;

	input_arr = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (!strncmp(input_arr[0], "/nick", 5))
		change_nick(e, cs, input_arr);
	if (!strncmp(input_arr[0], "/msg", 4))
		send_msg(e, input_arr, cs);
	else if (!strncmp(input_arr[0], "/join", 5))
		join_chan(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/leave", 6))
		leave_chan(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/who", 4))
		who_in_chan(e, cs, input_arr);
	ft_arrdel(input_arr);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	e->fds[cs].user.whisper = false;
}
