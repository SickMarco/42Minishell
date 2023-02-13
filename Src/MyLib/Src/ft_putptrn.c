/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:47:20 by mbozzi            #+#    #+#             */
/*   Updated: 2023/01/07 18:31:49 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

int	ft_putnbr_ptr(uintptr_t ptr, char *base)
{
	int		i;
	int		conv[100];
	int		ret;

	i = 0;
	ret = 0;
	if (!ptr)
		return (0);
	while (ptr >= 16)
	{
		conv[i] = base[ptr % 16];
		ptr = ptr / 16;
		i++;
	}
	conv[i] = base[ptr];
	while (i >= 0)
	{
		write(1, &conv[i], 1);
		i--;
		ret++;
	}
	return (ret);
}

int	ft_putptrn(uintptr_t ptr)
{
	int	len;

	len = 2;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	len += ft_putnbr_ptr(ptr, "0123456789abcdef");
	return (len);
}
