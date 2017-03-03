/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:37:57 by hivian            #+#    #+#             */
/*   Updated: 2017/03/03 17:14:16 by hivian           ###   ########.fr       */
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
			send(cs, "\b\b\b\033[31m>\033[0m ", 14, 0);
			send(cs, e->fds[i].user.nickname, \
				strlen(e->fds[i].user.nickname), 0);
			send(cs, "\n", 1, 0);
		}
		i++;
	}
}

void			join_chan(t_env *e, int cs, char **input_arr, t_user user)
{
	char		concat[CHAN_SIZE + 20];

	memset(concat, 0, CHAN_SIZE + 20);
	if (input_arr[1][0] == '#'  && strlen(input_arr[1]) > 3 \
	&& strlen(input_arr[1]) <= CHAN_SIZE)
	{
		memset(e->fds[cs].user.channel, 0, CHAN_SIZE);
		strcpy(e->fds[cs].user.channel, user.channel);
		strcat(concat, e->fds[cs].user.nickname);
		strcat(concat, " has joined channel\n");
		send_to_chan(e, concat, e->sock, user);
	}
}

void			change_nick(t_env *e, int cs, char **input_arr, t_user user)
{
	char		concat[NICK_SIZE * 2 + 22];
	char		tmp[NICK_SIZE];

	memset(concat, 0, NICK_SIZE * 2 + 22);
	memset(tmp, 0, NICK_SIZE);
	if (input_arr[1][0] != '#' && strlen(input_arr[1]) <= NICK_SIZE && \
	strcmp(ft_strtrim(input_arr[1]), ""))
	{
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
			send_to_chan(e, concat, e->sock, user);
		}
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
