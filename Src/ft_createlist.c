/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:56:47 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/21 19:11:19 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*ft_tabtolist(char **tab)
{
	int		i;
	t_list	*lst;

	i = 0;
	while (tab[i])
		i++;
	if (tab[i])
		free(tab[i]);
	lst = ft_lstnew(tab[--i]);
	if (!lst)
		return (NULL);
	while (--i >= 0)
	{
		ft_lstadd_front(&lst, ft_lstnew(tab[i]));
		if (!lst)
			return (NULL);
	}
	return (lst);
}

t_list	*ft_createlist(char **tab)
{
	t_list	*lst;

	lst = ft_tabtolist(tab);
	if (!lst)
		return (NULL);
	if (tab)
		free(tab);
	return (lst);
}
