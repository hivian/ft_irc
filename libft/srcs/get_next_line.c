/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 08:35:21 by hivian            #+#    #+#             */
/*   Updated: 2015/02/14 14:10:08 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*my_realloc(void *ptr, size_t size)
{
	void	*dup;

	if (!(dup = ft_memalloc(size)))
		return (NULL);
	ft_memcpy(dup, ptr, size);
	ft_memdel(&ptr);
	return (dup);
}

static void		my_copy(char **line, char *buff, int *i, int fd)
{
	int ret;
	int j;

	j = 0;
	while (buff[*i] != '\n' && buff[*i])
	{
		(*line)[j++] = buff[(*i)++];
		if (buff[*i] == '\0' && (ret = read(fd, buff, BUFF_SIZE)))
		{
			*line = my_realloc(*line, ft_strlen(*line) + (BUFF_SIZE + 1));
			buff[ret] = '\0';
			*i = 0;
		}
	}
	(*line)[j] = '\0';
}

int				get_next_line(int const fd, char **line)
{
	static char buff[BUFF_SIZE + 1];
	static int	ret = 0;
	static int	i = 0;

	if (!(*line = (char *)malloc(BUFF_SIZE + 1)))
		return (-1);
	ft_bzero(*line, ft_strlen(*line));
	if (ret == 0)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) <= 0)
			return (ret);
		buff[ret] = '\0';
	}
	my_copy(line, buff, &i, fd);
	if (buff[i] == '\n' && buff[i + 1] != '\0')
		i++;
	else
	{
		ret = 0;
		i = 0;
	}
	return (1);
}
