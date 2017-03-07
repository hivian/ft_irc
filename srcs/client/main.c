/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:29:52 by hivian            #+#    #+#             */
/*   Updated: 2017/03/07 12:06:28 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		get_localhost(t_env *e)
{
	char		*buf;
	char		*tmp;
	size_t		size;
	int			res;

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
			free(tmp);
			return ;
		}
	}
	free(tmp);
	free(e->addr);
	print_error("localhost not found");
}

static void				run_client(t_env *e)
{
	int					ret;

	printf("\033[1;30m- Connected to %s:%d\033[0m\n", e->addr, e->port);
	printf("\033[1;30m- /help : list of commmands\033[0m\n");
	//printf("\v\033[1;30m- Joined %s\033[0m\n", e->fds[e->sock].user.channel);
	while (true)
	{
		print_prompt(e);
		init_fd(e);
		e->ret = select(e->sock + 1, &e->fd_read, &e->fd_write, NULL, 0);
		check_fd(e);
		clean_input(e);
	}
}

static void				create_client(t_env *e)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	char				concat[NICK_SIZE];

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
	recv(e->sock, &e->get_id, sizeof(e->get_id), O_CLOEXEC);
	strcpy(e->fds[e->sock].user.channel, "#ft_irc-default");
	strcpy(concat, "Guest");
	e->id_to_str = ft_itoa(e->get_id);
	strcat(concat, e->id_to_str);
	strcpy(e->fds[e->sock].user.nickname, concat);
	send(e->sock, &e->fds[e->sock].user, sizeof(t_user), 0);
}

int				main(int ac, char **av)
{
	t_env		e;

	if (ac != 3)
		print_error(USAGE);
	if (!strcmp(av[1], "localhost"))
		get_localhost(&e);
	else
		e.addr = av[1];
	e.port = atoi(av[2]);
	init_env(&e);
	create_client(&e);
	run_client(&e);
	close(e.sock);
	free(e.fds);
	ft_strdel(&e.concat_recv);
	ft_strdel(&e.id_to_str);
	return (0);
}
