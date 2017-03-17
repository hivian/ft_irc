/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 08:58:18 by hivian            #+#    #+#             */
/*   Updated: 2017/03/17 11:27:15 by hivian           ###   ########.fr       */
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

void					print_prompt(t_env *e)
{
	ft_putstr("\033[36m");
	ft_putstr(e->nickname);
	ft_putstr(" $> ");
	ft_putstr("\033[0m");
}

void					clean_input(t_env *e)
{
	char				tmp[BUF_SIZE];

	memset(tmp, 0, BUF_SIZE);
	memset(tmp, '\b', NICK_SIZE + 4);
	ft_putstr(tmp);
	memset(tmp, 0, BUF_SIZE);
	memset(tmp, ' ', NICK_SIZE + 4);
	ft_putstr(tmp);
	memset(tmp, 0, BUF_SIZE);
	memset(tmp, '\b', NICK_SIZE + 4);
	ft_putstr(tmp);
}
