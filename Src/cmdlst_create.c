/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:44:07 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/13 12:38:52 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_cmdlst(t_list	*lst, t_data *ms)
{
	t_list	*lsthead;
	t_cmd	*head;
	t_cmd	*cmdlst;

	lsthead = lst;
	cmdlst = NULL;
	ft_cmd_addback(&cmdlst, ft_cmdnew(&lst, ms->path));
	head = cmdlst;
	while (lst)
	{
		if (!(ft_strncmp((char *)((lst)->content), "|",
						ft_sl((char *)((lst)->content)))))
		{
			free(lst->content);
			lst = lst->next;
		}
		else if (!(ft_strncmp((char *)((lst)->content), "<",
						ft_sl((char *)((lst)->content)))))
		{
			free(lst->content);
			lst = lst->next;
			if (!(lst))
				break ;
			cmdlst->in_fd = open((char *)((lst)->content), O_RDONLY);
			if (cmdlst->in_fd < 0)
				ft_perrex(cmdlst->cmds[0]);
			free((lst)->content);
			lst = lst->next;
		}
		else if (!(ft_strncmp((char *)(lst->content), "<<",
						ft_sl((char *)(lst->content)))))
		{
			free(lst->content);
			cmdlst->in_fd = open(HERED, O_RDONLY);
			if (cmdlst->in_fd < 0)
				ft_perrex(cmdlst->cmds[0]);
			lst = lst->next;
		}
		else if (!(ft_strncmp((char *)(lst->content), ">",
						ft_sl((char *)(lst->content)))))
		{
			free(lst->content);
			lst = lst->next;
			if (!(lst))
				break ;
			cmdlst->out_fd = open((char *)(lst->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (cmdlst->out_fd < 0)
				ft_perrex(cmdlst->cmds[0]);
			free(lst->content);
			lst = lst->next;
		}
		else if (!(ft_strncmp((char *)(lst->content), ">>",
						ft_sl((char *)(lst->content)))))
		{
			free(lst->content);
			lst = lst->next;
			if (!(lst))
				break ;
			cmdlst->out_fd = open((char *)(lst->content), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (cmdlst->out_fd < 0)
				ft_perrex(cmdlst->cmds[0]);
			free(lst->content);
			lst = lst->next;
		}
		else
			ft_cmd_addback(&cmdlst, ft_cmdnew(&lst, ms->path));
		cmdlst = ft_cmdlast(cmdlst);
	}
	ft_freelist(&lsthead);
	return (head);
}
