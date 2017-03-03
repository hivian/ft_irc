/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:06:45 by hivian            #+#    #+#             */
/*   Updated: 2017/03/03 16:04:35 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

//void		leave_chan(t_env *e, int cs, char **input_arr)
//{
	//memset(e->fds[e->sock].user.channel, 0, CHAN_SIZE);
//}

void		change_nick(t_env *e, int cs, char **input_arr)
{
	if (strlen(input_arr[1]) > NICK_SIZE)
		printf("\033[31mNickname too long\033[0m\n");
	else if (input_arr[1][0] == '#' || !strcmp(ft_strtrim(input_arr[1]), ""))
		printf("\033[31mNickname incorrect\033[0m\n");
	else
	{
		memset(e->nick_backup, 0, NICK_SIZE);
		strcpy(e->nick_backup, e->fds[e->sock].user.nickname);
		memset(e->fds[e->sock].user.nickname, 0, NICK_SIZE);
		strncpy(e->fds[e->sock].user.nickname, input_arr[1], \
		strlen(input_arr[1]) - 1);
	}
	send(e->sock, &e->fds[cs].user, sizeof(t_user), 0);
	send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
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
	}
	send(e->sock, &e->fds[cs].user, sizeof(t_user), 0);
	send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
}
