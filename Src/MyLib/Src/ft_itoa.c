/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:25:43 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:30:46 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

int	ft_number_size(int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num == -2147483648)
		return (11);
	if (num < 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		num;
	unsigned int	len;

	len = ft_number_size(n);
	num = (long int)n;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
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
