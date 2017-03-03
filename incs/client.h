/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 13:00:43 by hivian            #+#    #+#             */
/*   Updated: 2017/03/03 12:08:49 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

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
# define NICK_SIZE	16
# define CHAN_SIZE	50
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define MAX(a,b)	((a > b) ? a : b)
# define USAGE		"Usage: ./client <machine> <port>"

typedef struct		s_user
{
	char			channel[50];
	char			nickname[16];
	bool			whisper;
}					t_user;

typedef struct		s_fd
{
	int				type;
 	void			(*fct_read)();
	void			(*fct_write)();
 	char			buf_read[BUF_SIZE];
	char			buf_write[BUF_SIZE];
	t_user			user;
}					t_fd;

typedef struct		s_env
{
	int				maxfd;
	int				max;
	int				port;
	int				sock;
	char			*addr;
	int				ret;
	fd_set			fd_read;
	fd_set			fd_write;
	FILE			*file;
	char			strtime[26];
	char			concat_send[BUF_SIZE];
	char			concat_recv[BUF_SIZE];
	t_fd			*fds;
}					t_env;

void				init_fd(t_env *e);
void				init_env(t_env *e);
void				check_fd(t_env *e);
void				clean_fd(int i, t_env *e);
void				client_write(t_env *e, int cs);
void				client_read(t_env *e, int cs);
int					run_cmd(t_env *e, int cs);
void				change_nick(t_env *e, int cs, char **input_arr);
void				join_chan(t_env *e, int cs, char **input_arr);
void				print_error(char *str);
void				print_help(void);
void				get_time(t_env *e);
void				handle_signal(int sig);
void				clean_input(t_env *e);
int					gen_rand_nb(void);
void				print_prompt(t_env *e);

#endif
