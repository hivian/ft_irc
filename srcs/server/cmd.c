/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/02 11:48:28 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int				run_cmd(t_env *e, int cs, t_user user)
{
	char		**input_arr;

	if (e->fds[cs].buf_read[0] == '/')
	{
		input_arr = ft_strsplit(e->fds[cs].buf_read, ' ');
		if (!strcmp(input_arr[0], "/msg") && ft_arrlen(input_arr) > 2)
			send_msg(e, input_arr, cs);
		if (!strcmp(input_arr[0], "/join") && ft_arrlen(input_arr) == 2)
		{
			memset(e->fds[cs].user.channel, 0, CHAN_SIZE);
			strcpy(e->fds[cs].user.channel, user.channel);
			//send(cs, "")
		}
		else
		{
			send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
			send(cs, "Unknow command", 14, 0);
		}
		ft_arrdel(input_arr);
	}
	return (0);
}
