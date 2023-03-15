/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:56 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/15 16:05:02 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmdlst(t_cmd **cmdlst, t_cmd **head, t_list **lst, t_data *ms)
{
	*cmdlst = NULL;
	if (!(content_is(*lst, "|") || content_is(*lst, "<")
			|| content_is(*lst, "<<") || content_is(*lst, ">")
			|| content_is(*lst, ">>")))
		*cmdlst = ft_cmdnew(lst, ms->path);
	*head = *cmdlst;
}

void	clc_freelist(t_cmd *head, t_list **lsthead)
{
	if (!head)
		ft_freelistcont(*lsthead);
	ft_freelist(lsthead);
}
