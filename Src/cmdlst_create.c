/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:44:07 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/15 15:56:06 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	r_input(t_cmd *cmdlst, t_list **lst)
{
	lst_freecont_n_skip(lst);
	if (!(*lst))
		return (1);
	cmdlst->in_fd = open((char *)((*lst)->content), O_RDONLY);
	if (cmdlst->in_fd < 0)
		ft_perrex(cmdlst->cmds[0]);
	lst_freecont_n_skip(lst);
	return (0);
}

static void	r_heredoc(t_cmd *cmdlst, t_list **lst)
{
	lst_freecont_n_skip(lst);
	cmdlst->in_fd = open(HERED, O_RDONLY);
	if (cmdlst->in_fd < 0)
		ft_perrex(cmdlst->cmds[0]);
}

static int	r_output(t_cmd *cmdlst, t_list **lst)
{
	lst_freecont_n_skip(lst);
	if (!(*lst))
		return (1);
	cmdlst->out_fd = open((char *)((*lst)->content),
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (cmdlst->out_fd < 0)
		ft_perrex(cmdlst->cmds[0]);
	lst_freecont_n_skip(lst);
	return (0);
}

static int	r_append(t_cmd *cmdlst, t_list **lst)
{
	lst_freecont_n_skip(lst);
	if (!(*lst))
		return (1);
	cmdlst->out_fd = open((char *)((*lst)->content),
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (cmdlst->out_fd < 0)
		ft_perrex(cmdlst->cmds[0]);
	lst_freecont_n_skip(lst);
	return (0);
}

t_cmd	*create_cmdlst(t_list	*lst, t_data *ms)
{
	t_list	*lsthead;
	t_cmd	*head;
	t_cmd	*cmdlst;

	lsthead = lst;
	init_cmdlst(&cmdlst, &head, &lst, ms);
	while (lst && cmdlst)
	{
		if (content_is(lst, "|"))
			lst_freecont_n_skip(&lst);
		else if (content_is(lst, "<"))
			r_input(cmdlst, &lst);
		else if (content_is(lst, "<<"))
			r_heredoc(cmdlst, &lst);
		else if (content_is(lst, ">"))
			r_output(cmdlst, &lst);
		else if (content_is(lst, ">>"))
			r_append(cmdlst, &lst);
		else
			ft_cmd_addback(&cmdlst, ft_cmdnew(&lst, ms->path));
		cmdlst = ft_cmdlast(cmdlst);
	}
	clc_freelist(head, &lsthead);
	return (head);
}
