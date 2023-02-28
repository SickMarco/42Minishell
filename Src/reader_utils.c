/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:29:54 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/28 11:46:14 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_quotes(char *s, int *dc, int *sc)
{
	*dc = 0;
	*sc = 0;
	if (!s || !(*s))
		return ;
	while (*s)
	{
		if (*s == '\'')
			(*sc)++;
		else if (*s == '\"')
			(*dc)++;
		s++;
	}
}

void	ft_search_last_n_scale(char **origin, char c)
{
	int		lstx;
	int		i;
	char	*tmp;

	lstx = -1;
	i = 0;
	while (origin[0][i])
	{
		if (origin[0][i] == c)
			lstx = i;
		i++;
	}
	if (lstx > -1)
	{
		i = lstx;
		while (origin[0][i])
		{
			origin[0][i] = origin[0][i + 1];
			i++;
		}
		tmp = ft_strdup(*origin);
		free(*origin);
		*origin = tmp;
	}
}

char	*ft_sp(char *s)
{
	int	i;

	if (!s | !(*s))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != 32)
		i++;
	while (s[i] == 32)
		i++;
	if (s[i])
		return (&s[i]);
	return (NULL);
}

int	ft_lts(char *s)
{
	int	i;

	if (!s || !(*s))
		return (0);
	i = 0;
	while (s[i] && s[i] != 32)
		i++;
	return (i);
}
