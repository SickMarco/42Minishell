/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:44:07 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/09 14:11:30 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ****************************************************************************/

t_cmd	*create_cmdlst(t_list	**lst)
{
	t_cmd	*head;

	{
		else if (!(ft_strncmp((char *)((*lst)->content), "<",
						ft_sl((char *)((*lst)->content)))))
		{
			free((*lst)->content);
			*lst = (*lst)->next;
			if (!(*lst))
				break ;
			in_fd = open((char *)((*lst)->content), O_RDONLY);
			if (in_fd < 0)
				ft_perrex("open");
			free((*lst)->content);
			*lst = (*lst)->next;
		}
		else if (!(ft_strncmp((char *)((*lst)->content), ">",
						ft_sl((char *)((*lst)->content)))))
		{
			free((*lst)->content);
			*lst = (*lst)->next;
			if (!(*lst))
				break ;
			out_fd = open((char *)((*lst)->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (out_fd < 0)
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
			out_fd = open((char *)((*lst)->content), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (out_fd < 0)
				ft_perrex("open");
			free((*lst)->content);
			*lst = (*lst)->next;
		}
		else
			cmdlst_addback(&head, new_cmd());
	}
	free_lst();
}
