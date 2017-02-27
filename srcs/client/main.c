/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:29:52 by hivian            #+#    #+#             */
/*   Updated: 2017/02/27 10:10:29 by hivian           ###   ########.fr       */
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
	char				buf[BUF_SIZE + 1];
	int num;

	printf("Connected to server\n");
	while (true)
	{
		get_time(e);
		ft_putstr("\033[36m[");
		ft_putstr(e->strtime);
		ft_putstr("] Me $> \033[0m");
		if ((ret = read(0, buf, BUF_SIZE)) < 0)
		{
			close(e->sock);
			print_error("Disconnected");
		}
		buf[ret] = '\0';
		if ((send(e->sock, buf, BUF_SIZE, 0)) < 0)
			print_error("Failure sending message");
		else
		{
			ft_putstr("Client:Message being sent:");
			ft_putendl(buf);
            num = recv(e->sock, buf, sizeof(buf),0);
			if ( num <= 0 )
            {
                ft_putendl("Either Connection Closed or Error");
                break;
            }
            buf[num] = '\0';
			ft_putstr("Client:Message Received From Server -  ");
			ft_putendl(buf);
		}
	}
}

static void		create_client(t_env *e)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		print_error("getprotobyname error");
	e->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(e->port);
	sin.sin_addr.s_addr = inet_addr(e->addr);
	if (connect(e->sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		print_error("Connect error");
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
	create_client(&e);
	run_client(&e);
	close(e.sock);
	return (0);
}
