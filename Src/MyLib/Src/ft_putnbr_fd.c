/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:28:34 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:31:46 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	*num;
	int		len;
	int		i;

	i = 0;
	num = ft_itoa(n);
	len = ft_strlen(num);
	while (i < len)
	{
		write(fd, &num[i], 1);
		i++;
	}
}
