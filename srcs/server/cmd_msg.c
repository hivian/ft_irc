/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:12:24 by hivian            #+#    #+#             */
/*   Updated: 2017/03/16 10:20:16 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		check_error(t_env *e, int cs, char **input_arr)
{
	int			fd_dest;

	fd_dest = -1;
	if (ft_arrlen(input_arr) < 3)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Usage: /msg <nick> <message>\n");
	}
	else if ((fd_dest = get_fd_from_usr(e, input_arr[1])) < 0)
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m No such nick: ");
		strcat(e->fds[cs].buf_write, input_arr[1]);
		strcat(e->fds[cs].buf_write, "\n");
	}
	return (fd_dest);
}

void			send_msg(t_env *e, char **input_arr, int cs)
{
	int			i;
	int			fd_dest;

	i = 0;
	if ((fd_dest = check_error(e, cs, input_arr)) < 0)
		return ;
	else
	{
		i = 2;
		strcpy(e->fds[fd_dest].buf_write, "\033[33m*");
		strcat(e->fds[fd_dest].buf_write, e->fds[cs].user.nickname);
		strcat(e->fds[fd_dest].buf_write, "*\033[0m ");
		while (input_arr[i])
		{
			if (i != 2)
				strcat(e->fds[fd_dest].buf_write, " ");
			strcat(e->fds[fd_dest].buf_write, input_arr[i]);
			i++;
		}
	}
}
