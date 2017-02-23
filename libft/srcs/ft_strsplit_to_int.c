/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_to_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:50:52 by hivian            #+#    #+#             */
/*   Updated: 2015/02/14 08:50:49 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		convert_str_to_int(char *s, int *tab, int nb_value, char c)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	while (s[++i] && j < nb_value)
	{
		if ((s[0] != c && i == 0) || \
		(s[i] == c && s[i + 1] != c && s[i + 1] != '\0'))
			tab[++j] = ft_atoi(&s[i]);
	}
}

int				*ft_strsplit_to_int(char const *s, char c)
{
	int			*tab;
	int			nb_value;
	int			i;

	if (s == NULL)
		return (NULL);
	i = -1;
	nb_value = 0;
	while (s[++i])
	{
		if ((s[0] != c && i == 0) || \
			(s[i] == c && s[i + 1] != c && s[i + 1] != '\0'))
			nb_value++;
	}
	tab = (int *)malloc(sizeof(int) * nb_value);
	if (tab)
		convert_str_to_int((char *)s, tab, nb_value, c);
	else
		return (NULL);
	return (tab);
}
