/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/01 16:47:51 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int				run_cmd(t_env *e, int cs)
{
	char		**input_arr;

	if (e->fds[cs].buf_read[0] == '/')
	{
		input_arr = ft_strsplit(e->fds[cs].buf_read, ' ');
		if (!strcmp(input_arr[0], "/msg") && ft_arrlen(input_arr) > 2)
			send_msg(e, input_arr, cs);
		else
		{
			send(cs, &e->fds[e->sock].user, sizeof(t_user), 0);
			send(cs, "Unknow command", 14, 0);
		}
		ft_arrdel(input_arr);
	}
	return (0);
}
