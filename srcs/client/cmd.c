/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by hivian            #+#    #+#             */
/*   Updated: 2017/03/01 12:10:27 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int				run_cmd(t_env *e, int cs)
{
	char		**arr;

	printf("input = %s", e->fds[cs].buf_write);
	if (e->fds[cs].buf_write[0] == '/')
	{
		arr = ft_strsplit(e->fds[cs].buf_write, ' ');
		if (!strcmp(arr[0], "/msg") && ft_arrlen(arr) == 3)
		{
			
			while (*arr)
			{
				printf("> %s\n", *arr);
				arr++;
			}
		}
	}
	return (0);
}
