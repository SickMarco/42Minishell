/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:36:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/21 12:31:19 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_wordlen(char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != 32)
	{
		if (s[len] == 34)
			ft_close_quote(s, &len, 34);
		else if (s[len] == 39)
		{
			ft_close_quote(s, &len, 39);
			while (s[len] && s[len] != 32 && s[len] != 34 && s[len] != 39)
				len++;
		}
		else
			len++;
	}
	return (len);
}

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
		matrix[n] = ft_substr(s, i, ft_wordlen(&s[i]));
		if (!matrix[n])
			return (NULL);
		i += ft_wordlen(&s[i]);
		n++;
	}
	matrix[n] = NULL;
	return (matrix);
}
/*
#include <stdio.h>

int main()
{
	char s[] = "        echo vhello      therev how are 'you 'doing? $USER |wc -l >outfile  ";
	s[13] = 34;
	s[30] = 34;
	char **matrix;
	int i = 0;
	matrix = ft_split1(s);
	printf("\n\n\n\n");
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}*/
