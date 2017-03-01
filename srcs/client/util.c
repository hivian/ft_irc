/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 08:58:18 by hivian            #+#    #+#             */
/*   Updated: 2017/03/01 09:37:37 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void					print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(EXIT_FAILURE);
}

void					get_time(t_env *e)
{
	time_t				timer;
	struct tm			*tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(e->strtime, 26, "%Y-%m-%d %H:%M:%S", tm_info);
}

char					*fill_with(int len, char c)
{
	char				*buf;

	buf = (char*)malloc(sizeof(char) * len + 1);
	memset(buf, c, len);
	return (buf);
}

void					clean_buffer(t_env *e, char *nick)
{
	char				*tmp;

	tmp = fill_with(strlen(nick) + 4 + strlen(e->fds[e->sock].buf_write), '\b');
	ft_putstr(tmp);
	ft_strdel(&tmp);
	tmp = fill_with(strlen(nick) + 4 + strlen(e->fds[e->sock].buf_write), ' ');
	ft_putstr(tmp);
	ft_strdel(&tmp);
	if (e->fds[e->sock].buf_write[strlen(e->fds[e->sock].buf_write) - 1] != '\n')
	{
		//tmp = fill_with(strlen(nick) + 4
		ft_putstr("  \b\b");
	}
	tmp = fill_with(strlen(nick) + 4 + strlen(e->fds[e->sock].buf_write), '\b');
	ft_putstr(tmp);
	ft_strdel(&tmp);
}

static void		run_signal(int sig)
{
	(void)sig;
	printf("ENTER\n");
}

void			handle_signal(void)
{
	int		i;

	i = 0;
	signal(SIGINT, &run_signal);
}
