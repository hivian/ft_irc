/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/02 17:24:12 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			send_to_chan(t_env *e, char *message, int sock, t_user user)
{
	int			i;

	i = 0;
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && i != sock && \
		!strcmp(e->fds[i].user.channel, user.channel))
		{
			send(i, &e->fds[sock].user, sizeof(t_user), 0);
			send(i, message, strlen(message), 0);
		}
		i++;
	}
}

int				run_cmd(t_env *e, int cs, t_user user)
{
	char		**input_arr;
	char		concat[20 + NICK_SIZE];

	input_arr = ft_strsplit(e->fds[cs].buf_read, ' ');
	memset(concat, 0, 20 + NICK_SIZE);
	if (!strcmp(input_arr[0], "/msg") && ft_arrlen(input_arr) > 2)
		send_msg(e, input_arr, cs);
	else if (!strcmp(input_arr[0], "/join") && ft_arrlen(input_arr) == 2)
	{
		memset(e->fds[cs].user.channel, 0, CHAN_SIZE);
		strcpy(e->fds[cs].user.channel, user.channel);
		strcat(concat, e->fds[cs].user.nickname);
		strcat(concat, " has joined channel\n");
		send_to_chan(e, concat, e->sock, user);
	}
	else if (!strcmp(input_arr[0], "/leave") && ft_arrlen(input_arr) == 2)
	{
		//memset(e->fds[cs].user.channel, 0, CHAN_SIZE);
		//send(cs,)
	}
	/*else if (strcmp(input_arr[0], "/join"))
	{
		send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
		send(cs, "Unknow command\n", 14, 0);
	}*/
	ft_arrdel(input_arr);
	return (0);
}
