/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 08:58:18 by hivian            #+#    #+#             */
/*   Updated: 2017/02/27 09:07:58 by hivian           ###   ########.fr       */
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
