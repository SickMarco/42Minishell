/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:18:18 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:32:10 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	j = dest_len;
	if (size == 0 || size <= dest_len)
		return (size + src_len);
	while (src[i] != '\0' && i < (size - dest_len - 1))
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest_len + src_len);
}
