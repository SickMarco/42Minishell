/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:08:21 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:32:25 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (!to_find || !to_find[0])
		return ((char *)str);
	if (!to_find || !str)
		return (NULL);
	while (str[i] && i < len)
	{
		x = 0;
		while (i + x < len && str[i + x] == to_find[x] && to_find[x]
			&& str[i + x])
		{
			x++;
			if (to_find[x] == '\0' )
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
