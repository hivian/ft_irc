/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:48:53 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 15:18:37 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		is_valid_nick(char *nick)
{
	int			i;

	i = 0;
	while (nick[i])
	{
		if (!ft_isalnum(nick[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		check_error(t_env *e, int cs, char **input_arr)
{
	if (ft_arrlen(input_arr) != 2)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Usage: /nick <nickname>\n");
		return (-1);
	}
	else if (strlen(input_arr[1]) > NICK_SIZE)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Nickname too long\n");
		return (-1);
	}
	else if (!is_valid_nick(input_arr[1]))
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Invalid character(s)\n");
		return (-1);
	}
	return (1);
}

void			change_nick(t_env *e, int cs, char **input_arr)
{
	char		tmp[NICK_SIZE];

	memset(tmp, 0, NICK_SIZE);
	if ((check_error(e, cs, input_arr)) < 0)
		return ;
	strncpy(tmp, input_arr[1], strlen(input_arr[1]) - 1);
	if (duplicate_user(e, cs, tmp))
		send(cs, "Nickname is already in use\n", 27, 0);
	else
	{
		strcpy(e->fds[cs].buf_write, e->fds[cs].user.nickname);
		memset(e->fds[cs].user.nickname, 0, NICK_SIZE);
		strcpy(e->fds[cs].user.nickname, tmp);
		strcat(e->fds[cs].buf_write, " has changed nick to ");
		strcat(e->fds[cs].buf_write, e->fds[cs].user.nickname);
		strcat(e->fds[cs].buf_write, "\n");
		send_to_chan(e, e->fds[cs].buf_write, MSG_INFO, cs);
	}
}
