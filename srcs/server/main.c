/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:30:39 by hivian            #+#    #+#             */
/*   Updated: 2017/03/10 15:50:13 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void					print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(EXIT_FAILURE);
}

static void				run_server(t_env *e)
{
	struct timeval		waitd;

	//waitd = (struct timeval){5, 0};
	while (true)
	{
		init_fd(e);
		e->ret = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, 0);
		check_fd(e);
	}
	free(e->fds);
}

static void				create_server(t_env *e)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		print_error("getprotobyname error");
	e->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(e->port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(e->sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		print_error("Bind error");
	listen(e->sock, 42);
	e->fds[e->sock].type = FD_SERV;
	e->fds[e->sock].fct_read = srv_accept;
	memset(e->fds[e->sock].user.channel, 0, 50);
	memset(e->fds[e->sock].user.nickname, 0, 16);
	e->fds[e->sock].user.whisper = false;
}

int						main(int ac, char **av)
{
	t_env				e;

	if (ac != 2)
		print_error(USAGE);
	e.port = atoi(av[1]);
	init_env(&e);
	create_server(&e);
	run_server(&e);
	close(e.sock);
	return (0);
}
