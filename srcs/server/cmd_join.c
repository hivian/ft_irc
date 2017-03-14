/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:46:26 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 16:25:28 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		check_error(t_env *e, int cs, char **input_arr)
{
	if (ft_arrlen(input_arr) != 2)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Usage: /join <#channel>\n");
	}
	else if (strlen(input_arr[1]) > CHAN_SIZE)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Channel name too long\n");
	}
	else if (input_arr[1][0] != '#')
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Channel name must begin with #\n");
	}
	else if (strlen(input_arr[1]) < 4)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Channel name too short\n");
	}
	else
		return (1);
	return (-1);
}

void			join_chan(t_env *e, int cs, char **input_arr)
{
	char		concat[CHAN_SIZE + NICK_SIZE + 9];

	if ((check_error(e, cs, input_arr)) < 0)
		return ;
	memset(concat, 0, CHAN_SIZE + NICK_SIZE + 9);
	get_time(e);
	strcpy(concat, e->fds[cs].user.nickname);
	strcat(concat, " leaved ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	send_to_chan(e, concat, MSG_INFO, cs);
	printf("\033[31m[%s]\033[0m %s leaved %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
	memset(e->fds[cs].user.channel, 0, CHAN_SIZE);
	strncpy(e->fds[cs].user.channel, input_arr[1], strlen(input_arr[1]) - 1);
	memset(concat, 0, CHAN_SIZE + NICK_SIZE + 9);
	strcpy(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	send_to_chan(e, concat, MSG_INFO, cs);
	printf("\033[31m[%s]\033[0m %s joined %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
}
