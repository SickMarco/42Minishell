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

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->cmd != NULL)
			free(cmd->cmd);
		i = -1;
		while (cmd->cmds[++i])
			free(cmd->cmds[i]);
		free(cmd->cmds);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

void	free_for_all(t_data **ms)
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
	free(*ms);
}

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
