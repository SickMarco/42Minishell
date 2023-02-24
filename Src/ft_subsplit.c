/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:40:32 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/24 14:42:17 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_sl(const char *s)
{
	int	i;

	if (!s || !(*s))
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_rl(t_list **arg, int sin, int slen)
{
	t_list	*nn;
	char	*so;

	nn = (*arg)->next;
	so = (char *)((*arg)->content);
	(*arg)->next = ft_lstnew(ft_substr(so, sin, slen));
	if (so[sin + slen])
	{
		(*arg)->next->next = ft_lstnew(ft_substr(so, sin + slen,
					ft_sl(&(so[sin + slen]))));
		(*arg)->next->next->next = nn;
	}
	else
		(*arg)->next->next = nn;
	(*arg)->content = ft_substr(so, 0, sin);
}

static void	ft_reassemblelist(t_list **arg, int sin, int slen)
{
	t_list	*nn;
	char	*so;

	so = (char *)((*arg)->content);
	if (slen == 2 && ft_sl(so) == 2)
		return ;
	nn = (*arg)->next;
	if (sin)
		ft_rl(arg, sin, slen);
	else
	{
		(*arg)->next = ft_lstnew(ft_substr(so, sin + 1, ft_sl(&(so)[sin + 1])));
		(*arg)->next->next = nn;
		(*arg)->content = ft_substr(so, sin, slen);
	}
	free(so);
}

static void	ft_splitlist(t_list *args)
{
	int		i;
	char	*s;

	while (args)
	{
		i = -1;
		s = (char *)(args->content);
		while (s[++i])
		{
			if (ft_strlen(s) > 1 && ft_ischarofset(s[i], "|<>"))
			{
				if (s[i + 1]
					&& ft_ischarofset(s[i + 1], "<>") && s[i] == s[i + 1])
				{
					ft_reassemblelist(&(args), i, 2);
					i++;
				}
				else
					ft_reassemblelist(&(args), i, 1);
			}
		}
		args = args->next;
	}
}

t_list	*ft_subsplit(char **tab)
{
	t_list	*args;

	args = ft_createlist(tab);
	if (!args)
		return (NULL);
	ft_splitlist(args);
	return (args);
}
