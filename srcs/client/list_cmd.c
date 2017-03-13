/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:06:45 by hivian            #+#    #+#             */
/*   Updated: 2017/03/13 16:08:30 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		connect_to(t_env *e, char **input_arr)
{
	close(e->sock);
	free(e->fds);
	ft_strdel(&e->addr);
	ft_strdel(&e->id_to_str);
	clear_list(e->list);
	free(e);
	connect_to_server(ft_arrlen(input_arr), input_arr);
}

void		change_nick(t_env *e, int cs, char **input_arr)
{
	if (strlen(input_arr[1]) > NICK_SIZE)
		printf("\033[31mNickname too long\033[0m\n");
	else if (input_arr[1][0] == '#' || input_arr[1][0] == '\n')
		printf("\033[31mNickname incorrect\033[0m\n");
	else
	{
		memset(e->nick_backup, 0, NICK_SIZE);
		strcpy(e->nick_backup, e->fds[e->sock].user.nickname);
		memset(e->fds[e->sock].user.nickname, 0, NICK_SIZE);
		strncpy(e->fds[e->sock].user.nickname, input_arr[1], \
		strlen(input_arr[1]) - 1);
		send(e->sock, &e->fds[cs].user, sizeof(t_user), 0);
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	}
}

void		join_chan(t_env *e, int cs, char **input_arr)
{
	if (strlen(input_arr[1]) > CHAN_SIZE)
		printf("\033[31mChannel name too long\033[0m\n");
	else if (input_arr[1][0] != '#')
		printf("\033[31mChannel must begin with #\033[0m\n");
	else if (strlen(input_arr[1]) < 4)
		printf("\033[31mChannel name too short\033[0m\n");
	else
	{
		memset(e->fds[e->sock].user.channel, 0, CHAN_SIZE);
		strncpy(e->fds[e->sock].user.channel, input_arr[1], \
		strlen(input_arr[1]) - 1);
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	}
}

void		leave_chan(t_env *e, int cs, char **input_arr)
{
	char	*trim;

	trim = ft_strtrim(input_arr[1]);
	if (strlen(input_arr[1]) > CHAN_SIZE)
		printf("\033[31mChannel name too long\033[0m\n");
	else if (input_arr[1][0] != '#')
		printf("\033[31mChannel must begin with #\033[0m\n");
	else if (strlen(input_arr[1]) < 4)
		printf("\033[31mChannel name too short\033[0m\n");
	else if (!strcmp(trim, CHAN_GEN))
		printf("\033[31mYou can't leave %s\033[0m\n", CHAN_GEN);
	else if (strcmp(trim, e->fds[cs].user.channel))
		printf("\033[31mYour channel is %s\033[0m\n", e->fds[cs].user.channel);
	else
	{
		memset(e->fds[e->sock].user.channel, 0, CHAN_SIZE);
		strncpy(e->fds[e->sock].user.channel, CHAN_GEN, strlen(CHAN_GEN));
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	}
	ft_strdel(&trim);
}

void		send_msg(t_env *e, int cs, char **input_arr)
{
	int		maxsize;
	char	*concat_msg;

	maxsize = BUF_SIZE - 6 - NICK_SIZE;
	concat_msg = NULL;
	concat_arr(&concat_msg, input_arr);
	if (strlen(concat_msg) > maxsize)
	{
		memset(e->fds[cs].buf_write, 0, BUF_SIZE);
		strncpy(e->fds[cs].buf_write, concat_msg, maxsize);
	}
	send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	ft_strdel(&concat_msg);
}
