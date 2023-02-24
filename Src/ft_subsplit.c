/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:40:32 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/24 12:19:40 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ischarofset(char c, char *set)
{
	size_t	i;

	if (!set || !(*set) || !c)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_reassemblelist(t_list **arg, int sin, int slen)
{
	t_list	*nn;
	char	*sm;
	char	*so; 

	nn = (*arg)->next;
	so = (char *)((*arg)->content);
	sm = ft_substr(so, sin, slen);
	if (sin)
	{
		(*arg)->next = ft_lstnew(sm);//create middle
		if (so[sin + slen])//if there are 3 nodes
		{
			(*arg)->next->next = ft_lstnew(ft_substr(so, sin + slen, ft_strlen(&(so[sin + slen]))));//create next of middle
			(*arg)->next->next->next = nn;//attach to the next of middle the rest of the list
		}
		else
			(*arg)->next->next = nn;//attach to middle the rest of the list
		(*arg)->content = ft_substr(so, 0, sin);//new content of start node
//		printf("%s\n", ss);
//		free((*arg)->content);//free previous content of start
//		(*arg)->content = ss;
	}
	else
	{
		(*arg)->next = ft_lstnew(ft_substr(so, sin + 1, ft_strlen(&(so)[sin + 1])));
		(*arg)->next->next = nn;
		(*arg)->content = sm;
	}
	free(so);
}

void	ft_splitlist(t_list *args)
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
				if (s[i + 1] && ft_ischarofset(s[i + 1], "<>") && s[i] == s[i + 1])
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
//	ft_print_slst(args);///
//	if (!args)
//		return (NULL);
	ft_splitlist(args);
//	ft_print_slst(args);///
	return (args);
}
