/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/09 17:18:43 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	custom_exec(t_data **ms, t_cmd *cmd)
{
	struct stat	info;

	if (!stat(cmd->cmds[0], &info) && (S_ISDIR(info.st_mode)))
	{
		g_exit = 126;
		printf("smashell: %s: Is a directory\n", (*ms)->cmd[0]);
	}
	else if (!access(cmd->cmds[0], X_OK))
	{
		execve(cmd->cmds[0], cmd->cmds, (*ms)->env);
		perror("smashell");
	}
	else if (!access(cmd->cmds[0], F_OK))
	{
		g_exit = 126;
		perror("smashell");
	}
	else
		no_cmd(cmd);
	exit(EXIT_FAILURE);
}

void	executor(t_data **ms, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->cmd && cmd->in_fd != -1)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
		execve(cmd->cmd, cmd->cmds, NULL);
		perror("smashell");
		exit (EXIT_FAILURE);
	}
	else if (!cmd->cmd && (*ms)->hist)
		custom_exec(ms, cmd);
	else if (cmd && (*ms)->hist)
	{
		execve(cmd->cmd, cmd->cmds, (*ms)->env);
		perror("smashell");
		exit (EXIT_FAILURE);
	}
	if (!access(HERED, F_OK))
		unlink(HERED);
	return ;
}

void	prnt_ctrl(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}
