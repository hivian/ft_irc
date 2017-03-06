/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/06 12:31:35 by hivian           ###   ########.fr       */
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

	input_arr = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (!strcmp(input_arr[0], "/nick") && ft_arrlen(input_arr) == 2)
		change_nick(e, cs, input_arr, user);
	if (!strcmp(input_arr[0], "/msg") && ft_arrlen(input_arr) > 2)
		send_msg(e, input_arr, cs);
	else if (!strcmp(input_arr[0], "/join") && ft_arrlen(input_arr) == 2)
		join_chan(e, cs, input_arr, user);
	else if (!strcmp(input_arr[0], "/who\n") && ft_arrlen(input_arr) == 1)
		who(e, cs, user);
	ft_arrdel(input_arr);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	return (0);
}
