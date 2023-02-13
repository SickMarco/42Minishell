/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:34:22 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/11 18:02:38 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mylib.h"

t_stack	*ft_lstlastnum(t_stack *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_stack	*ft_lstnewnum(int num)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->num = num;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_backnum(t_stack **lst, t_stack *new)
{
	t_stack	*last;

	if (*lst)
	{
		last = ft_lstlastnum(*lst);
		last->next = new;
		new->next = NULL;
	}
	else
		*lst = new;
}

void	ft_lstadd_frontnum(t_stack **lst, t_stack *new)
{
	new->next = *lst;
	*lst = new;
}

int	ft_lstsizenum(t_stack *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
