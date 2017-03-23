/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 13:00:43 by hivian            #+#    #+#             */
/*   Updated: 2017/03/17 13:28:59 by hivian           ###   ########.fr       */
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

# define BUF_SIZE	4096
# define NICK_SIZE	9
# define CHAN_GEN	"#ft_irc-default"
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define MAX(a,b)	((a > b) ? a : b)
# define USAGE		"Usage: ./client <machine> <port>"

typedef struct addrinfo		t_addrinfo;

typedef struct		s_node
{
	char			*nickname;
	struct s_node	*next;
}					t_node;

typedef struct		s_slist
{
	t_node			*head;
}					t_slist;

typedef struct		s_fd
{
	int				type;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
}					t_fd;

typedef struct		s_env
{
	int				maxfd;
	int				max;
	int				port;
	int				sock;
	char			*addr;
	char			nickname[NICK_SIZE + 1];
	int				ret;
	fd_set			fd_read;
	fd_set			fd_write;
	FILE			*file;
	int				get_id;
	t_fd			*fds;
	char			nick_backup[NICK_SIZE + 1];
	t_slist			*list;
	t_addrinfo		*servinfo;
}					t_env;

void				init_fd(t_env *e);
void				init_env(t_env *e);
void				check_fd(t_env *e);
void				clean_fd(int i, t_env *e);
void				client_write(t_env *e, int cs);
void				client_read(t_env *e, int cs);
void				connect_to_server(int count_arg, char **args);
void				run_cmd(t_env *e, int cs);
void				send_msg(t_env *e, int cs, char **input_arr);
void				concat_arr(char **concat_msg, char **input_arr);
void				print_error(char *str);
void				get_time(t_env *e);
void				clean_input(void);
void				print_prompt(t_env *e);

t_slist				*create_list(void);
void				clear_list(t_slist *list);
void				print_list(t_slist *list);
void				list_push_back(t_slist *list, char *data);
void				del_node(t_slist *list, char *data);
int					is_ignored(t_slist *list, char *data);

#endif
