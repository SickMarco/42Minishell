/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:56:47 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/22 15:29:54 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_slst(t_list *lst)
{
	int	i;

	if (!lst)
	{
		printf("(Null)\n");
		return (0);
	}
	i = 1;
	printf("%s", ((char *)(lst->content)));
	while (lst->next)
	{
		lst = lst->next;
		printf("\n%s", ((char *)(lst->content)));
		i++;
	}
	printf("\n");
	return (i);
}

static t_list	*ft_tabtolist(char **tab)
{
	int		i;
	t_list	*lst;

	i = 0;
	while (tab[i])
		i++;
//	if (tab[i])
//		free(tab[i]);
	lst = ft_lstnew(tab[--i]);
//	printf("%s\n", (char *)(lst->content));
	if (!lst)
		return (NULL);
	while (--i >= 0)
	{
		ft_lstadd_front(&lst, ft_lstnew(tab[i]));
//		if (!lst)
//			return (NULL);
//		printf("%s\n", (char *)(lst->content));
	}
//	ft_print_slst(lst);
	return (lst);
}

t_list	*ft_createlist(char **tab)
{
	t_list	*lst;

	lst = ft_tabtolist(tab);
	if (!lst)
		return (NULL);
//	if (tab)
//		free(tab);
//	ft_print_slst(lst);
//	printf("%p\n", lst);
//	printf("%s\n", (char *)(lst->content));
	return (lst);
}
