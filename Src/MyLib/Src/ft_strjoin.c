/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:50:00 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:32:07 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		x;

	i = 0;
	x = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[x])
	{
		str[i] = s2[x];
		i++;
		x++;
	}
	str[i] = '\0';
	return (str);
}
