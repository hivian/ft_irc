/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:06:45 by hivian            #+#    #+#             */
/*   Updated: 2017/03/03 12:07:41 by hivian           ###   ########.fr       */
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
	else if (input_arr[1][0] == '#')
		printf("\033[31mNickname incorrect\033[0m\n");
	else
	{
		memset(e->fds[e->sock].user.nickname, 0, NICK_SIZE);
		strncpy(e->fds[e->sock].user.nickname, input_arr[1], \
		strlen(input_arr[1]) - 1);
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
	}
}
