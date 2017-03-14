/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/03/14 11:07:32 by hivian           ###   ########.fr       */
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

static char			*trim_name(char *s)
{
	char	*str;
	size_t	len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (i < 6)
	{
		i++;
		s++;
	}
	len = ft_strlen(s);
	while (len > 6)
		len--;
	str = ft_strndup(s, len);
	return (str);
}

static void			print_recv(t_env *e, int cs, char *buf)
{
	char			**input_arr;
	char			*trim;

	input_arr = ft_strsplit(buf, ' ');
	trim = trim_name(input_arr[0]);
	if (is_ignored(e->list, trim))
		return ;
	clean_input(e);
	printf("%s", e->fds[cs].buf_read);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE);
	ft_arrdel(input_arr);
	ft_strdel(&trim);
}

void				client_read(t_env *e, int cs)
{
	int					ret;
	int					i;

	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) <= 0)
	{
		close(cs);
		clean_fd(cs, e);
		clean_input(e);
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
