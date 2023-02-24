/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:36:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/24 12:20:27 by mabaffo          ###   ########.fr       */
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
int main()
{
	char s[] = "        echo vhello      therev how are 'you 'doing? $USER a|wc -l >outfile  ";
	s[13] = 34;
	s[30] = 34;
	char **matrix;
	int i = 0;
	matrix = ft_split1(s);
//	printf("\n\n\n\n");
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
//	printf("\n\n");
	printf("\n\n\n\n");
	t_list *lst;
//	lst = ft_createlist(matrix);
	lst = ft_subsplit(matrix);
//printf("%s", ((char *)(lst->content)));
//	ft_print_slst(lst);
//	printf("\n\n\n\n");
//	ft_subsplit(&(lst));
	ft_print_slst(lst);
//	printf("\n\n\n\n");
}*/
