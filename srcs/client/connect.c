/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:39:42 by hivian            #+#    #+#             */
/*   Updated: 2017/03/16 10:12:26 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void				get_localhost(t_env *e)
{
	char				*buf;
	char				*tmp;
	size_t				size;
	int					res;

	buf = NULL;
	size = 0;
	if ((e->file = fopen("/etc/hosts", "r")) < 0)
		print_error("Error opening file");
	while (getline(&buf, &size, e->file) > 0)
	{
		e->addr = (char*)malloc(sizeof(char) * strlen(buf) + 1);
		tmp = (char*)malloc(sizeof(char) * strlen(buf) + 1);
		if ((res = sscanf(buf, "%s %s", e->addr, tmp)) > 0 && \
		!strcmp(tmp, "localhost"))
		{
			ft_strdel(&tmp);
			ft_strdel(&buf);
			return ;
		}
		ft_strdel(&tmp);
		ft_strdel(&e->addr);
		ft_strdel(&buf);
	}
	print_error("localhost not found");
}

static void				run_client(t_env *e)
{
	printf("\033[1;30m- Connected to %s:%d\033[0m\n", e->addr, e->port);
	printf("\033[1;30m- /help : list of commmands\033[0m\n");
	while (true)
	{
		clean_input(e);
		print_prompt(e);
		init_fd(e);
		e->ret = select(e->sock + 1, &e->fd_read, &e->fd_write, NULL, 0);
		check_fd(e);
	}
}

static void				create_client(t_env *e)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	char				concat[NICK_SIZE + 1];

	if (getaddrinfo(e->addr, NULL, NULL, &e->servinfo))
		print_error("getaddrinfo error");
	proto = getprotobyname("tcp");
	if (!proto)
		print_error("getprotobyname error");
	e->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(e->port);
	sin.sin_addr.s_addr = inet_addr(e->addr);
	if (connect(e->sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		print_error("Connect error");
	e->fds[e->sock].type = FD_CLIENT;
	e->fds[e->sock].fct_write = client_write;
	e->fds[e->sock].fct_read = client_read;
	recv(e->sock, e->nickname, NICK_SIZE, 0);
}

void					connect_to_server(int count_arg, char **args)
{
	t_env				*e;

	e = (t_env *)malloc(sizeof(t_env));
	e->list = create_list();
	if (count_arg < 3)
	{
		e->addr = strdup("127.0.0.1");
		e->port = 4242;
	}
	else
	{
		if (!strcmp(args[1], "localhost"))
			get_localhost(e);
		else
			e->addr = args[1];
		e->port = atoi(args[2]);
	}
	init_env(e);
	create_client(e);
	run_client(e);
	close(e->sock);
	free(e->fds);
	ft_strdel(&e->addr);
	free(e);
}
