/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 08:58:18 by hivian            #+#    #+#             */
/*   Updated: 2017/03/01 11:41:24 by hivian           ###   ########.fr       */
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

int						gen_rand_nb(void)
{
	srand(time(NULL));

	return(rand() % 99999);
}

void					print_prompt(t_env *e)
{
	//printf("len1 = %lu\n", strlen("\033[36m"));
	//printf("len2 = %lu\n", strlen("\033[0m"));
	ft_putstr("\033[36m");
	ft_putstr(e->fds[e->sock].nickname);
	ft_putstr(" $> ");
	ft_putstr("\033[0m");
}

void					clean_input(t_env *e, char *nick)
{
	char				tmp[BUF_SIZE];

	memset(tmp, 0, BUF_SIZE);
	memset(tmp, '\b', strlen(nick) + 4 + strlen(e->fds[e->sock].buf_write));
	ft_putstr(tmp);
	memset(tmp, 0, BUF_SIZE);
	memset(tmp, ' ', strlen(nick) + 4 + strlen(e->fds[e->sock].buf_write));
	ft_putstr(tmp);
	memset(tmp, 0, BUF_SIZE);
	memset(tmp, '\b', strlen(nick) + 4 + strlen(e->fds[e->sock].buf_write));
	if (e->fds[e->sock].buf_write[strlen(e->fds[e->sock].buf_write) - 1] != '\n')
		ft_putstr("  \b\b");
	ft_putstr(tmp);
	memset(tmp, 0, BUF_SIZE);
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
