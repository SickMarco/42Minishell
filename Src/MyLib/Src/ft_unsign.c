/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:17:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:32:44 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

unsigned int	ft_number_size_unsigned(unsigned int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char			*str;
	unsigned int	num;
	unsigned int	len;

	len = ft_number_size_unsigned(n);
	num = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (num == 0)
		str[0] = '0';
	str[len] = '\0';
	while (num != 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}

int	ft_unsign(int num)
{
	char			*str;
	int				i;
	int				len;
	unsigned int	n;

	len = 0;
	i = 0;
	n = (unsigned int)num;
	str = ft_itoa_unsigned(n);
	while (str[i])
		write(1, &str[i++], 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}
