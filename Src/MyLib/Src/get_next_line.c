/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:21:15 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:32:59 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

int	ft_ncount(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] && buff[i] == '\n')
		i++;
	return (i);
}

char	*ft_exline(char *buff)
{
	int		i;
	int		x;
	int		len;
	char	*ex;

	x = 0;
	i = ft_ncount(buff);
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	len = ft_strlen(buff) - i + 1;
	ex = ft_calloc(sizeof(char), len);
	if (!ex)
		return (NULL);
	while (buff[i])
		ex[x++] = buff[i++];
	free(buff);
	return (ex);
}

char	*ft_newline(char *buff)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	i = ft_ncount(buff);
	tmp = ft_calloc(sizeof(char), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		tmp[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		tmp[i] = '\n';
	return (tmp);
}

char	*ft_read(int fd, int *flag)
{
	char		*tmp;
	int			check;

	tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	check = read(fd, tmp, BUFFER_SIZE);
	*flag = check;
	if (check == -1)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	int			flag;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	if (!buff)
		buff = ft_calloc(sizeof(char), 1);
	flag = 1;
	while (flag > 0)
	{
		tmp = ft_read(fd, &flag);
		buff = ft_strjoin2(buff, tmp);
		free(tmp);
		if (ft_check_eol(buff) == 1)
			break ;
	}
	line = ft_newline(buff);
	buff = ft_exline(buff);
	return (line);
}
