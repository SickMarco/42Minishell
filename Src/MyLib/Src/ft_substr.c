/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:08:32 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:32:33 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		if (i >= start && x < len)
		{
			dest[x] = s[i];
			x++;
		}
		i++;
	}
	dest[x] = 0;
	return (dest);
}
