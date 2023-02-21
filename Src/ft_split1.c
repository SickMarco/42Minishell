/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:36:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/21 11:05:13 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split1(char *s)
{
	char	**matrix;
	int		wc;
	int		n;
	int		i;

	wc = ft_countwords1(s);
	matrix = (char **)malloc((wc + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	if (!s || !(*s))
		matrix[0] = NULL;
	n = 0;
	i = 0;
	while (n < wc)
	{
		ft_skip_space(s, &i);
		matrix[n] = ft_substr1(s, i, );
		
	}
	matrix[n] = NULL;
	return (matrix);
}
/*
while (n < wc)
	{
		while (s[i] == 32)
			i++;
		matrix[n] = ft_substr((char *)s, i, unc(&((char *)s)[i], 32));
		if (!matrix[n])
			return (NULL);
		i += unc(&((char *)s)[i], 32);
		n++;
	}
	matrix[ct] = NULL;
	return (matrix);
*/
