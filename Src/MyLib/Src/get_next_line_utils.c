/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:39:01 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/07 18:33:34 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		x;

	i = 0;
	x = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(sizeof(char), len + 1);
	if (!str || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[x])
		str[i++] = s2[x++];
	str[i] = '\0';
	free (s1);
	return (str);
}

int	ft_check_eol(char *buff)
{
	int	x;

	x = 0;
	while (buff[x])
	{
		if (buff[x] == '\n')
			return (1);
		x++;
	}
	return (0);
}

char	*ft_strjoin3(char *s1, char *s2, int flag)
{
	char	*str;
	int		len;
	int		i;
	int		x;

	i = 0;
	x = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(sizeof(char), len + 1);
	if (!str || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[x])
		str[i++] = s2[x++];
	str[i] = '\0';
	if (flag == 0)
		free (s1);
	else if (flag == 1)
		free (s2);
	return (str);
}
