/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:37:57 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 12:05:55 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
