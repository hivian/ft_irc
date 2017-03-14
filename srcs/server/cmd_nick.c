/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:48:53 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 15:39:22 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		is_valid_nick(char *nick)
{
	int			i;

	i = 0;
	while (nick[i] && nick[i] != '\n')
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
	char		concat[NICK_SIZE * 2 + 22];

	memset(tmp, 0, NICK_SIZE);
	memset(concat, 0, NICK_SIZE * 2 + 22);
	if ((check_error(e, cs, input_arr)) < 0)
		return ;
	strncpy(tmp, input_arr[1], strlen(input_arr[1]) - 1);
	if (duplicate_user(e, cs, tmp))
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Nickname is already in use\n");
	}
	else
	{
		strcpy(concat, e->fds[cs].user.nickname);
		memset(e->fds[cs].user.nickname, 0, NICK_SIZE);
		strcpy(e->fds[cs].user.nickname, tmp);
		strcat(concat, " has changed nick to ");
		strcat(concat, e->fds[cs].user.nickname);
		strcat(concat, "\n");
		send_to_chan(e, concat, MSG_INFO, cs);
	}
}
