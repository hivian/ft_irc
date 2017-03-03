/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/03 12:10:00 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			print_help(void)
{
	printf("===================== - List of commands - ====================\n");
	printf("#                                                             #\n");
	printf("#    /nick <nickname>           : change your nickname        #\n");
	printf("#    /join, /leave [#channel]                                 #\n");
	printf("#    /who                       : who is logged ?             #\n");
	printf("#    /msg <nick> <message>                                    #\n");
	printf("#    /connect <machine> [port]                                #\n");
	printf("#                                                             #\n");
	printf("===============================================================\n");
}

int				run_cmd(t_env *e, int cs)
{
	char		**input_arr;

	//printf("input = %s", e->fds[cs].buf_write);
	if (e->fds[cs].buf_write[0] == '/')
	{
		input_arr = ft_strsplit(e->fds[cs].buf_write, ' ');
		clean_input(e);
		if (!strcmp(input_arr[0], "/nick") && ft_arrlen(input_arr) == 2)
			change_nick(e, cs, input_arr);
		else if (!strcmp(input_arr[0], "/join") && ft_arrlen(input_arr) == 2)
			join_chan(e, cs, input_arr);
		//else if (!strcmp(input_arr[0], "/quit\n") && ft_arrlen(input_arr) == 1)
		//	leave_chan(e, cs, input_arr);
		else if (!strcmp(input_arr[0], "/help\n"))
			print_help();
		else if (!strcmp(input_arr[0], "/msg") && ft_arrlen(input_arr) > 2)
		{}
		else
			printf("\033[31mUnknow command\033[0m\n");
		ft_arrdel(input_arr);
	}
	return (0);
}
