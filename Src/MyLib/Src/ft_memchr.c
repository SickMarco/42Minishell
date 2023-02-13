/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:05:50 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:31:21 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return ((void *)str);
		i++;
		str++;
	}
	return (NULL);
}
