/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/02 12:38:02 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		leave_chan(t_env *e, int cs, char **input_arr)
{
	//memset(e->fds[e->sock].user.channel, 0, CHAN_SIZE);
}

static void		join_chan(t_env *e, int cs, char **input_arr)
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
		strcpy(e->fds[e->sock].user.channel, input_arr[1]);
	}
}

int				run_cmd(t_env *e, int cs)
{
	char		**input_arr;

	//printf("input = %s", e->fds[cs].buf_write);
	if (e->fds[cs].buf_write[0] == '/')
	{
		input_arr = ft_strsplit(e->fds[cs].buf_write, ' ');
		clean_input(e);
		if (!strcmp(input_arr[0], "/join") && ft_arrlen(input_arr) == 2)
			join_chan(e, cs, input_arr);
		if (!strcmp(input_arr[0], "/quit") && ft_arrlen(input_arr) == 1)
			leave_chan(e, cs, input_arr);
		else if (strcmp(input_arr[0], "/msg"))
			printf("\033[31mUnknow command\033[0m\n");
		ft_arrdel(input_arr);
	}
	return (0);
}
