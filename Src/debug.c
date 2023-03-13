/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:49:23 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/13 12:52:02 by mabaffo          ###   ########.fr       */
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

void	print_cmdlst(t_cmd *cmdn)
{
	t_cmd	*nxt;
	int		i;
	int		n;

	n = -1;
	while (cmdn)
	{
		printf("cmd node %d:\n", ++n);
		nxt = cmdn->next;
		i = -1;
		while ((cmdn->cmds)[++i])
			printf("\tcmds[%d] = %s\n", i, (cmdn->cmds)[i]);
		printf("\n\tpath = %s\n", cmdn->cmd);
		printf("\n\t in_fd = %d\n\t out_fd = %d\n\n", cmdn->in_fd, cmdn->out_fd);
		cmdn = nxt;
	}
}
