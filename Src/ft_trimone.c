/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:58:24 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/24 18:15:39 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isextchar(char c, char *s)
{
	if (!s || !(*s) || !c)
		return (0);
	if (s[0] == c && s[ft_strlen(s) - 1] == c)
		return (1);
	return (0);
}

static void	ft_trimex(char **arg)
{
	int		i;
	char	*s;

	i = -1;
	(*arg)[ft_strlen(*arg) - 1] = '\0';
	while ((*arg)[++i])
		(*arg)[i] = (*arg)[i + 1];
	s = ft_strdup(*arg);
	if (!s)
		return ;
	free(*arg);
	*arg = s;
}

static void	ft_trimin(char **arg)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	while ((*arg)[++i])
	{
		if ((*arg)[i] == '\'')
		{
			j = i - 1;
			while ((*arg)[++j])
				(*arg)[j] = (*arg)[j + 1];
			s = ft_strdup(*arg);
			if (!s)
				return ;
			free(*arg);
			*arg = s;
			i--;
		}
	}
}

void	ft_trimone(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (!ft_isextchar('\"', args[i]))
			ft_trimin(&(args[i]));
	}
	i = -1;
	while (args[++i])
	{
		if (ft_isextchar('\"', args[i]))
			ft_trimex(&(args[i]));
	}
}
/*
//trimin, trimmare ' non esterne e non dentro ". es. 'you 'doing?
//trimex, trimmare ' e " esterne
*/

/*****************************************************************
 
 !TO DO!

 fare check prima di split1:
 * se numero di ' e' dispari o numero di " e' dispari:
 * * trova il primo tipo di quote, fai gnl(0)

*/
