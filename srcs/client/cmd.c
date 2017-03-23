/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/23 09:22:09 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		ignore_nick(t_env *e, char **input_arr)
{
	char		nick_ignored[NICK_SIZE + 1];
	char		*str;

	str = "to unignore type: /UNIGNORE";
	memset(nick_ignored, 0, NICK_SIZE + 1);
	if (ft_arrlen(input_arr) == 1)
		print_list(e->list);
	else if (input_arr[1][0] == '\n')
		printf("\033[31mNickname incorrect\033[0m\n");
	else if (strlen(input_arr[1]) - 1 > NICK_SIZE)
		printf("\033[31mNickname too long\033[0m\n");
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

static void		unignore_nick(t_env *e, char **input_arr)
{
	char		nick_ignored[NICK_SIZE + 1];

	memset(nick_ignored, 0, NICK_SIZE + 1);
	if (input_arr[1][0] == '\n')
		printf("\033[31mNickname incorrect\033[0m\n");
	else if (strlen(input_arr[1]) - 1 > NICK_SIZE)
		printf("\033[31mNickname too long\033[0m\n");
	else
	{
		strncpy(nick_ignored, input_arr[1], strlen(input_arr[1]) - 1);
		del_node(e->list, nick_ignored);
		printf("\033[31mUnignored %s.\033[0m\n", nick_ignored);
	}
}

static void		connect_to(t_env *e, int cs, char **input_arr)
{
	close(e->sock);
	free(e->fds);
	ft_strdel(&e->addr);
	clear_list(e->list);
	clean_fd(cs, e);
	connect_to_server(ft_arrlen(input_arr), input_arr);
}

void			run_cmd(t_env *e, int cs)
{
	char		**input_arr;

	input_arr = ft_strsplit(e->fds[cs].buf_write, ' ');
	if (!strncmp(input_arr[0], "/connect", 8))
		connect_to(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/ignore", 7) && ft_arrlen(input_arr) < 3)
		ignore_nick(e, input_arr);
	else if (!strcmp(input_arr[0], "/unignore") && ft_arrlen(input_arr) == 2)
		unignore_nick(e, input_arr);
	else
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	if (!strncmp(input_arr[0], "/nick", 5) && ft_arrlen(input_arr) == 2 && \
	strlen(input_arr[1]) - 1 <= NICK_SIZE)
		strncpy(e->nick_backup, input_arr[1], strlen(input_arr[1]) - 1);
	ft_arrdel(input_arr);
}
