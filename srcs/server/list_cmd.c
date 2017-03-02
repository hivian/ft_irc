/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:37:57 by hivian            #+#    #+#             */
/*   Updated: 2017/03/02 10:13:27 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"


void			send_msg(t_env *e, char **input_arr, int cs)
{
	int			fd_dest;
	char		tmp[30];
	int			i;

	if ((fd_dest = get_fd_from_usr(e, input_arr[1])) < 0)
	{
		strcpy(tmp, "No such nick: ");
		strcat(tmp, input_arr[1]);
		send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
		send(cs, tmp, strlen(tmp), 0);
		send(cs, "\n", 1, 0);
	}
	else if (strlen(input_arr[2]) > BUF_SIZE)
	{
		send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
		send(cs, "Message too long\n", 17, 0);
	}
	else
	{
		i = 2;
		e->fds[cs].user.whisper = true;
		send(fd_dest, &e->fds[cs].user, sizeof(t_user), 0);
		while (input_arr[i])
		{
			if (i != 2)
				send(fd_dest, " ", 1, 0);
			send(fd_dest, input_arr[i], strlen(input_arr[i]), 0);
			i++;
		}
		e->fds[cs].user.whisper = false;
	}
}
