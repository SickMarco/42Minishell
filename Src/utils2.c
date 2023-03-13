/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:27:14 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/13 12:29:09 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_for_all2(t_data **ms)
{
	int	i;

	i = -1;
	while ((*ms)->env[++i])
		free((*ms)->env[i]);
	i = -1;
	while ((*ms)->path[++i])
		free((*ms)->path[i]);
	free((*ms)->path);
	free((*ms)->prompt);
	free((*ms)->input);
	free((*ms)->env);
	free_cmd((*ms)->cmd_list);
	free(*ms);
}

void	ft_perrex(char *s)
{
	perror(s);
	g_exit = 1234;
}

void	ft_freelist(t_list **lst)
{
	t_list	*nxt;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		nxt = (*lst)->next;
		free((*lst));
		*lst = nxt;
	}
	free(*lst);
}

void	lst_freecont_n_skip(t_list **lst)
{
	free((*lst)->content);
	*lst = (*lst)->next;
}

int	content_is(t_list *lst, const char *s)
{
	if (!(ft_strncmp((char *)((lst)->content), s,
			ft_sl((char *)((lst)->content)))))
		return (1);
	else
		return (0);
}
