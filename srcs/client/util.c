/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 08:58:18 by hivian            #+#    #+#             */
/*   Updated: 2017/03/23 09:23:26 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void					print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(EXIT_FAILURE);
}

void					print_prompt(t_env *e)
{
	ft_putstr("\033[36m");
	ft_putstr(e->nickname);
	ft_putstr(" $> ");
	ft_putstr("\033[0m");
}

void					clean_input(void)
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
