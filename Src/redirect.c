/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:34:27 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/16 15:50:04 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_redir(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmds[0], "cd", 3))
	{
		if (cmd->out_fd != -1)
		{
			close(STDOUT_FILENO);
			dup2(cmd->out_fd, STDOUT_FILENO);
			close(cmd->out_fd);
		}
		if (cmd->in_fd != -1)
		{
			close(STDIN_FILENO);
			dup2(cmd->in_fd, STDIN_FILENO);
			close(cmd->in_fd);
		}
	}
}

void	close_redir(t_data **ms, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmds[0], "cd", 3))
	{
		if (cmd->out_fd != -1)
			dup2((*ms)->stdout_fd, STDOUT_FILENO);
		if (cmd->in_fd != -1)
			dup2((*ms)->stdin_fd, STDIN_FILENO);
	}
}
