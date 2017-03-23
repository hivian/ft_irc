/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:37:29 by hivian            #+#    #+#             */
/*   Updated: 2017/03/17 14:00:56 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
	len = ft_strlen(s) - 5;
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
	{
		ft_arrdel(input_arr);
		ft_strdel(&trim);
		return ;
	}
	clean_input();
	printf("%s", e->fds[cs].buf_read);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE + 1);
	ft_arrdel(input_arr);
	ft_strdel(&trim);
}

void				client_write(t_env *e, int cs)
{
	if (e->fds[cs].buf_write[0] == '/')
	{
		clean_input();
		run_cmd(e, cs);
	}
	else if (e->fds[cs].buf_write[0] != '\n')
		send(e->sock, e->fds[cs].buf_write, strlen(e->fds[cs].buf_write), 0);
	memset(e->fds[cs].buf_write, 0, BUF_SIZE + 1);
}

void				client_read(t_env *e, int cs)
{
	int					ret;
	char				nick_changed[NICK_SIZE + 21];

	if ((ret = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) <= 0)
	{
		close(cs);
		clean_fd(cs, e);
		clean_input();
		print_error("\033[31mServer disconnected\033[0m");
	}
	e->fds[cs].buf_read[ret] = '\0';
	memset(nick_changed, 0, NICK_SIZE + 21);
	strncpy(nick_changed, e->nickname, strlen(e->nickname));
	strcat(nick_changed, " has changed nick to");
	if (ft_strstr(e->fds[e->sock].buf_read, nick_changed))
	{
		memset(e->nickname, 0, NICK_SIZE + 1);
		strcpy(e->nickname, e->nick_backup);
		memset(e->nick_backup, 0, NICK_SIZE + 1);
	}
	print_recv(e, cs, e->fds[cs].buf_read);
}
