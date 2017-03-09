/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/09 15:55:21 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		print_help(void)
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

static void		ignore_nick(t_env *e, int cs, char **input_arr)
{
	char		nick_ignored[NICK_SIZE];
	char		*str;

	str = "to unignore type: /UNIGNORE";
	memset(nick_ignored, 0, NICK_SIZE);
	if (input_arr[1][0] == '\n')
		printf("\033[31mNickname incorrect\033[0m\n");
	else
	{
		strncpy(nick_ignored, input_arr[1], strlen(input_arr[1]) - 1);
		if (!is_ignored(e->list, nick_ignored))
		{
			list_push_back(e->list, nick_ignored);
			printf("\033[31mIgnored %s, %s %s\033[0m\n", \
				nick_ignored, str, nick_ignored);
		}
	}
}

static void		unignore_nick(t_env *e, int cs, char **input_arr)
{
	char		nick_ignored[NICK_SIZE];

	memset(nick_ignored, 0, NICK_SIZE);
	strncpy(nick_ignored, input_arr[1], strlen(input_arr[1]) - 1);
	if (input_arr[1][0] == '\n')
		printf("\033[31mNickname incorrect\033[0m\n");
	else
	{
		del_node(e->list, nick_ignored);
		printf("\033[31mUnignored %s\033[0m\n", nick_ignored);
	}
}

static void		who_in_chan(t_env *e, int cs)
{
	e->cmd_who = true;
	send(e->sock, &e->fds[cs].user, sizeof(t_user), 0);
	send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
}

void			run_cmd(t_env *e, int cs)
{
	char		**input_arr;

	input_arr = ft_strsplit(e->fds[cs].buf_write, ' ');
	if (!strcmp(input_arr[0], "/nick") && ft_arrlen(input_arr) == 2)
		change_nick(e, cs, input_arr);
	else if (!strcmp(input_arr[0], "/connect") && ft_arrlen(input_arr) == 3)
		connect_to(e, cs, input_arr);
	else if (!strcmp(input_arr[0], "/join") && ft_arrlen(input_arr) == 2)
		join_chan(e, cs, input_arr);
	else if (!strcmp(input_arr[0], "/leave") && ft_arrlen(input_arr) == 2)
		leave_chan(e, cs, input_arr);
	else if (!strcmp(input_arr[0], "/help\n") && ft_arrlen(input_arr) == 1)
		print_help();
	else if (!strcmp(input_arr[0], "/msg") && ft_arrlen(input_arr) > 2)
		send_msg(e, cs, input_arr);
	else if (!strcmp(input_arr[0], "/ignore") && ft_arrlen(input_arr) == 2)
		ignore_nick(e, cs, input_arr);
	else if (!strcmp(input_arr[0], "/unignore") && ft_arrlen(input_arr) == 2)
		unignore_nick(e, cs, input_arr);
	else if (!strcmp(input_arr[0], "/who\n") && ft_arrlen(input_arr) == 1)
		who_in_chan(e, cs);
	else
		printf("\033[31mUnknow command\033[0m\n");
	ft_arrdel(input_arr);
}
