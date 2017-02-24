/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:30:39 by hivian            #+#    #+#             */
/*   Updated: 2017/02/24 10:29:43 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void					print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(EXIT_FAILURE);
}

static void				run_server(t_env *e)
{
	init_env(e);
	while (true)
	{
		init_fd(e);
		e->ret = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
		check_fd(e);
	}
	free(e->fds);
}

static int				create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		print_error("Bind error");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		print_error("Bind error");
	listen(sock, 42);
	return (sock);
}

int				main(int ac, char **av)
{
	t_env		e;
	int			port;
	int			sock;

	if (ac != 2)
		print_error(USAGE);
	port = atoi(av[1]);
	sock = create_server(port);
	run_server(&e);
	close(sock);
	return (0);
}
