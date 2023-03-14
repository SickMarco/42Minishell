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

int	ft_isextchar(char c, char *s)
{
	if (!s || !(*s) || !c)
		return (0);
	if (s[0] == c && s[ft_strlen(s) - 1] == c)
		return (1);
	return (0);
}

void	ft_trimex(char **arg)
{
	int		i;
	char	*s;

	if (!ft_isextchar('\"', *arg))
		return ;
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

void	ft_trimin(char **arg)
{
	int		i;
	int		j;
	char	*s;
	
	if (ft_isextchar('\"', *arg))
		return ;
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

void	ft_lstiter2(t_list *lst, void (*f)(char **))
{
	char **cont;

	if (!f)
		return ;
	while (lst)
	{
		cont = (char **)(&(lst->content));
		(*f)(cont);
		lst = lst->next;
	}
}

void	ft_trimlist(t_list	*lst)
{
	ft_lstiter2(lst, ft_trimin);
	ft_lstiter2(lst, ft_trimex);
}
/*
//trimin, trimmare ' non esterne e non dentro ". es. 'you 'doing?
//trimex, trimmare ' e " esterne
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
*/