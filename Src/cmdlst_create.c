/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:44:07 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/09 20:46:19 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ****************************************************************************/

#include "../minishell.h"

void	ft_perrex(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	ft_freelist(t_list **lst)
{
	t_list	*nxt;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		nxt = (*lst)->next;
//		if ((*lst)->content)
//			free((*lst)->content);
		free((*lst));
		*lst = nxt;
	}
}

t_cmd	*create_cmdlst(t_list	**lst, t_data *ms)
{
	t_list	**lsthead;
	t_cmd	*head;
	t_cmd	*cmdlst;
/*
	ft_print_slst(*lst);
	return NULL;*/
	lsthead = lst;
	cmdlst = ft_cmdnew(lst, ms->path);
	head = cmdlst;
	while (*lst)
	{
		if (!(ft_strncmp((char *)((*lst)->content), "|",
						ft_sl((char *)((*lst)->content)))))
		{
			free((*lst)->content);
			*lst = (*lst)->next; 
		}
		else if (!(ft_strncmp((char *)((*lst)->content), "<",
						ft_sl((char *)((*lst)->content)))))
		{
			free((*lst)->content);
			*lst = (*lst)->next;
			if (!(*lst))
				break ;
			cmdlst->in_fd = open((char *)((*lst)->content), O_RDONLY);
			if (cmdlst->in_fd < 0)
				ft_perrex("open");
			free((*lst)->content);
			*lst = (*lst)->next;
		}
		else if (!(ft_strncmp((char *)((*lst)->content), "<<",
						ft_sl((char *)((*lst)->content)))))///modifica readifyouneed in modo da lasciare << come nodo di lst
		{
			free((*lst)->content);
			cmdlst->in_fd = open(HERED, O_RDONLY);
			if (cmdlst->in_fd < 0)
				ft_perrex("open");
			*lst = (*lst)->next;
		}
		else if (!(ft_strncmp((char *)((*lst)->content), ">",
						ft_sl((char *)((*lst)->content)))))
		{
			free((*lst)->content);
			*lst = (*lst)->next;
			if (!(*lst))
				break ;
			cmdlst->out_fd = open((char *)((*lst)->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (cmdlst->out_fd < 0)
				ft_perrex("open");
			free((*lst)->content);
			*lst = (*lst)->next;
		}
		else if (!(ft_strncmp((char *)((*lst)->content), ">>",
						ft_sl((char *)((*lst)->content)))))
		{
			free((*lst)->content);
			*lst = (*lst)->next;
			if (!(*lst))
				break ;
			cmdlst->out_fd = open((char *)((*lst)->content), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (cmdlst->out_fd < 0)
				ft_perrex("open");
			free((*lst)->content);
			*lst = (*lst)->next;
		}
		else
			ft_cmd_addback(&cmdlst, ft_cmdnew(lst, ms->path));//scorre lst nodes
	}
	ft_freelist(lsthead);//free just the nodes, not the contents
	return (head);
}
