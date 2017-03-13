/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:37:57 by hivian            #+#    #+#             */
/*   Updated: 2017/03/13 17:12:44 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			who(t_env *e, int cs)
{
	int			i;

	i = 0;
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && \
		!strcmp(e->fds[i].user.channel, e->fds[cs].user.channel))
		{
			strcat(e->fds[cs].buf_write, "\033[31m> \033[0m");
			strcat(e->fds[cs].buf_write, e->fds[i].user.nickname);
			strcat(e->fds[cs].buf_write, "\n");
		}
		i++;
	}
}

void			join_chan(t_env *e, int cs, char **input_arr)
{
	char		concat[CHAN_SIZE + NICK_SIZE + 9];

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

void			leave_chan(t_env *e, int cs, char **input_arr, t_user user)
{
	char		concat[CHAN_SIZE + NICK_SIZE + 9];

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
	strncpy(e->fds[cs].user.channel, CHAN_GEN, strlen(CHAN_GEN));
	memset(concat, 0, CHAN_SIZE + NICK_SIZE + 9);
	strcpy(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, CHAN_GEN);
	strcat(concat, "\n");
	send_to_chan(e, concat, MSG_INFO, cs);
	printf("\033[31m[%s]\033[0m %s joined %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
}

void			change_nick(t_env *e, int cs, char **input_arr, t_user user)
{
	char		concat[NICK_SIZE * 2 + 22];
	char		tmp[NICK_SIZE];

	memset(concat, 0, NICK_SIZE * 2 + 22);
	memset(tmp, 0, NICK_SIZE);
	if (duplicate_user(e, cs, user.nickname))
		send(cs, "Nickname is already in use\n", 27, 0);
	else
	{
		strcpy(tmp, e->fds[cs].user.nickname);
		memset(e->fds[cs].user.nickname, 0, NICK_SIZE);
		strcpy(e->fds[cs].user.nickname, user.nickname);
		strcat(concat, tmp);
		strcat(concat, " has changed nick to ");
		strcat(concat, e->fds[cs].user.nickname);
		strcat(concat, "\n");
		send_to_chan(e, concat, MSG_INFO, e->sock);
	}
}

void			send_msg(t_env *e, char **input_arr, int cs)
{
	int			fd_dest;
	int			i;

	memset(e->fds[cs].buf_write, 0, BUF_SIZE);
	if ((fd_dest = get_fd_from_usr(e, input_arr[1])) < 0)
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m No such nick: ");
		strcat(e->fds[cs].buf_write, input_arr[1]);
		strcat(e->fds[cs].buf_write, "\n");
	}
	else
	{
		i = 2;
		e->fds[cs].user.whisper = true;
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
