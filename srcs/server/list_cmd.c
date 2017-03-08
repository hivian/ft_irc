/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:37:57 by hivian            #+#    #+#             */
/*   Updated: 2017/03/08 13:51:45 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		who(t_env *e, int cs, t_user user)
{
	int		i;

	i = 0;
	send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && \
		!strcmp(e->fds[i].user.channel, user.channel))
		{
			send(cs, "> ", 2, 0);
			send(cs, e->fds[i].user.nickname, \
				strlen(e->fds[i].user.nickname), 0);
			send(cs, "\n", 1, 0);
		}
		i++;
	}
}

void			join_chan(t_env *e, int cs, char **input_arr, t_user user)
{
	char		concat[CHAN_SIZE + 9];
	char		tmp[CHAN_SIZE];

	memset(tmp, 0, CHAN_SIZE);
	memset(concat, 0, CHAN_SIZE + 9);
	get_time(e);
	strcat(concat, e->fds[cs].user.nickname);
	strcat(concat, " leaved ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	strcpy(tmp, e->fds[cs].user.channel);
	memset(e->fds[cs].user.channel, 0, CHAN_SIZE);
	strcpy(e->fds[cs].user.channel, user.channel);
	send_to_chan(e, concat, e->sock, tmp);
	memset(concat, 0, CHAN_SIZE + 9);
	strcat(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	send_to_chan(e, concat, e->sock, user.channel);
	printf("\033[31m[%s]\033[0m %s leaved %s\n", \
		e->strtime, e->fds[cs].user.nickname, tmp);
	printf("\033[31m[%s]\033[0m %s joined %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
}

void			leave_chan(t_env *e, int cs, char **input_arr, t_user user)
{
	char		concat[CHAN_SIZE + 9];
	char		tmp[CHAN_SIZE];

	memset(tmp, 0, CHAN_SIZE);
	memset(concat, 0, CHAN_SIZE + 9);
	get_time(e);
	strcat(concat, e->fds[cs].user.nickname);
	strcat(concat, " leaved ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	strcpy(tmp, e->fds[cs].user.channel);
	memset(e->fds[cs].user.channel, 0, CHAN_SIZE);
	strcpy(e->fds[cs].user.channel, user.channel);
	send_to_chan(e, concat, e->sock, tmp);
	memset(concat, 0, CHAN_SIZE + 9);
	strcat(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, CHAN_GEN);
	strcat(concat, "\n");
	send_to_chan(e, concat, e->sock, user.channel);
	printf("\033[31m[%s]\033[0m %s leaved %s\n", \
		e->strtime, e->fds[cs].user.nickname, tmp);
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
	{
		send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
		send(cs, "Nickname is already in use\n", 27, 0);
	}
	else
	{
		strcpy(tmp, e->fds[cs].user.nickname);
		memset(e->fds[cs].user.nickname, 0, NICK_SIZE);
		strcpy(e->fds[cs].user.nickname, user.nickname);
		strcat(concat, tmp);
		strcat(concat, " has changed nick to ");
		strcat(concat, e->fds[cs].user.nickname);
		strcat(concat, "\n");
		send_to_chan(e, concat, e->sock, user.channel);
	}
}

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
