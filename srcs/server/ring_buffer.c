/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:41:22 by hivian            #+#    #+#             */
/*   Updated: 2017/03/23 09:25:00 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void			handle_buf(t_env *e, int cs, char *buf)
{
	if (buf[0] == '/')
		run_cmd(e, cs, buf);
	else
		send_to_chan(e, buf, MSG_STD, cs);
}

void				ring_buffer_write(t_env *e, int cs, char *msg)
{
	char			buf[BUF_SIZE + 1];
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	memset(buf, 0, BUF_SIZE + 1);
	if (msg[strlen(msg) - 1] == '\n')
		handle_buf(e, cs, msg);
	else
	{
		while (msg[i] != '\n')
			i++;
		i++;
		while (j < strlen(msg))
		{
			if (i > BUF_SIZE - 13 - NICK_SIZE)
				i = 0;
			buf[j++] = msg[i++];
		}
		handle_buf(e, cs, buf);
	}
}

void				ring_buffer_read(t_env *e, int cs, char *msg)
{
	static char		buf[BUF_SIZE + 1];
	size_t			i;
	static int		j = -1;

	i = 0;
	if (j == -1)
	{
		memset(buf, 0, BUF_SIZE + 1);
		j = 0;
	}
	while (msg[i])
	{
		if (j > BUF_SIZE - 13 - NICK_SIZE)
			j = 0;
		buf[j++] = msg[i++];
	}
	if (ft_strchr(buf, '\n'))
	{
		ring_buffer_write(e, cs, buf);
		memset(buf, 0, BUF_SIZE + 1);
		j = 0;
	}
}
