/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:29:21 by hivian            #+#    #+#             */
/*   Updated: 2017/02/23 12:04:07 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H
# define FT_IRC_H

# include "../libft/incs/libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/select.h>
# include <sys/time.h>
# include <stdbool.h>

# define BUF_SIZE	4096
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define MAX(a,b)	((a > b) ? a : b)

typedef struct	s_fd
{
	int			type;
 	void		(*fct_read)();
	void		(*fct_write)();
 	char		buf_read[BUF_SIZE + 1];
	char		buf_write[BUF_SIZE + 1];
}				t_fd;

typedef struct		s_env
{
	t_fd			*fds;
	int				port;
	int				sock;
	int				maxfd;
	int				max;
	int				r;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_env;

#endif
