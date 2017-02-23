/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:47:20 by hivian            #+#    #+#             */
/*   Updated: 2014/11/09 12:44:35 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	d;
	int		start;
	int		end;
	char	**tab;

	i = 0;
	d = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(*tab) * (ft_strlen(s) / 2 + 2))))
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
			tab[d++] = ft_strsub(s, start, (end - start));
	}
	tab[d] = NULL;
	return (tab);
}
