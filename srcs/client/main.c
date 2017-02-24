/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:29:52 by hivian            #+#    #+#             */
/*   Updated: 2017/02/24 14:59:35 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void					print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(EXIT_FAILURE);
}

static void		get_localhost(t_env *e)
{
	char		*buf;
	size_t		size;
	int			res;

	buf = NULL;
	size = 0;
	if ((e->file = fopen("/etc/hosts", "r")) < 0)
		print_error("Error opening file");
	while (getline(&buf, &size, e->file) > 0)
	{
		e->localhost = (char*)malloc(sizeof(char) * strlen(buf) + 1);
		if ((res = sscanf(buf, "%s prout", e->localhost)) > 0)
		{
			printf("TOTO\n");
			return ;
		}
		free(e->localhost);
	}
	print_error("localhost not found");
}

int				main(int ac, char **av)
{
	t_env		e;

	if (ac != 3)
		print_error(USAGE);
	if (!strcmp(av[1], "localhost"))
		get_localhost(&e);
	printf("%s\n", e.localhost);
	return (0);
}
