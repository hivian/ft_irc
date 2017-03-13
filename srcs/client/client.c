/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/03/13 16:28:06 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				client_write(t_env *e, int cs)
{
	if (e->fds[cs].buf_write[0] == '/')
	{
		clean_input(e);
		run_cmd(e, cs);
	}
	else if (e->fds[cs].buf_write[0] != '\n')
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	memset(e->fds[cs].buf_write, 0, BUF_SIZE);
}

static void			print_recv(t_env *e, int cs, char *buf)
{
	char			**input_arr;

	clean_input(e);
	input_arr = ft_strsplit(buf, ' ');
	printf("HERE = %s\n", input_arr[0]);
	input_arr[0]++;
	if (is_ignored(e->list, input_arr[0]))
		return ;
	printf("%s", e->fds[cs].buf_read);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	ft_arrdel(input_arr);
}

void				client_read(t_env *e, int cs)
{
	int					ret;
	int					i;

	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) <= 0)
	{
		close(cs);
		clean_fd(cs, e);
		print_error("\033[31mServer disconnected\033[0m");
	}
	e->fds[cs].buf_read[ret] = '\0';
	if (!strcmp(e->fds[e->sock].buf_read, "Nickname is already in use\n"))
	{
		memset(e->fds[e->sock].user.nickname, 0, NICK_SIZE);
		strcpy(e->fds[e->sock].user.nickname, e->nick_backup);
	}
	print_recv(e, cs, e->fds[cs].buf_read);
}
