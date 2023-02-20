/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:47:01 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/20 20:32:04 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_skip_space(char *s, int *i)
{
	while (s[*i] && s[*i] == 32)
		(*i)++;
}

void	ft_close_quote(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	(*i)++;
}

int	ft_countwords(char *s)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	if (!s || !(*s))
		return (0);
	ft_skip_space(s, &i);
	while (s[i])
	{
		words++;
		while (s[i] && s[i] != 32)
		{
			if (s[i] == 34)
			{
				if (s[i - 1] && s[i - 1] != 32)
					words++;
				ft_close_quote(s, &i, 34);
			}
			else if (s[i] == 39)
			{
				if (s[i - 1] && s[i - 1] != 32)
					words++;
				ft_close_quote(s, &i, 39);
				while (s[i] && s[i] != 32 && s[i] != 34 && s[i] != 39)
					i++;
			}
			else
				i++;
		}
		ft_skip_space(s, &i);
	}
	return (words);
}

int main(int ac, char **av)
{
	char s[] = "ciao come stai                                                                   ";
	s[17] = 97;

	s[18] = 34;
	s[22] = 34;

	s[24] = 39;
	s[26] = 39;
	s[23] = 65;
	printf("words = %d\n",ft_countwords(s));
}
/*
char **ft_splitone(char *s)
{

}*/
/*
static long long int	countstr(char *s, char c)
{
	long long int	i;
	long long int	n;

	if (!s || !(*s))
		return (0);
	n = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && (i == 0 || s[i - 1] != c))
			n++;
		i++;
	}
	if ((ft_strlen(s) >= 2) && (i == 0 || s[i - 1] != c))
		n++;
	return (n);
}

static long long int	unc(char *s, char c)
{
	long long	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	long long	i;
	long long	scount;
	long long	ct;
	char		**matrix;

	i = 0;
	ct = 0;
	scount = countstr((char *)s, c);
	matrix = (char **)malloc((scount + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	if (!s || s[0] == '\0' || c == '\0')
		matrix[0] = NULL;
	while (ct < scount)
	{
		while (s[i] == c)
			i++;
		matrix[ct] = ft_substr((char *)s, i, unc(&((char *)s)[i], c));
		if (!matrix[ct])
			return (NULL);
		i += unc(&((char *)s)[i], c);
		ct++;
	}
	matrix[ct] = NULL;
	return (matrix);
}*/
