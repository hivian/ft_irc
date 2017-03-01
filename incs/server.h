/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:29:21 by hivian            #+#    #+#             */
/*   Updated: 2017/03/01 16:48:40 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

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

# define BUF_SIZE	512
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define MAX(a,b)	((a > b) ? a : b)
# define USAGE		"Usage : ./serveur <port>"

typedef struct		s_user
{
	char			channel[50];
	char			nickname[16];
}					t_user;

typedef struct		s_fd
{
	int				type;
 	void			(*fct_read)();
	void			(*fct_write)();
 	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
	t_user			user;
}					t_fd;

typedef struct		s_env
{
	t_fd			*fds;
	int				port;
	int				sock;
	int				maxfd;
	int				max;
	int				ret;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_env;

void				init_fd(t_env *e);
void				init_env(t_env *e);
void				check_fd(t_env *e);
void				srv_accept(t_env *e);
int					run_cmd(t_env *e, int cs);
void				send_msg(t_env *e, char **input_arr, int cs);
int					get_fd_from_usr(t_env *e, char *name);
void				clean_fd(int i, t_env *e);
void				print_error(char *str);

#endif
