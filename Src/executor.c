/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/11 16:03:31 by mbozzi           ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
	else if (!access(cmd->cmds[0], F_OK))
	{
		g_exit = 126;
		perror("smashell");
	}
	else
	{
		no_cmd(cmd);
		free_for_all2(ms);
		exit(EXIT_SUCCESS);
	}
	exit(g_exit);
}

void	exec_here(t_data **ms, t_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_calloc(sizeof(char *), 2);
	tmp[0] = ft_strdup(cmd->cmds[0]);
	while (cmd->cmds[++i])
		free(cmd->cmds[i]);
	free(cmd->cmds);
	cmd->cmds = tmp;
	(*ms)->fd = open(HERED, O_RDONLY);
	dup2((*ms)->fd, STDIN_FILENO);
	close((*ms)->fd);
	execve(cmd->cmd, cmd->cmds, (*ms)->env);
	perror("smashell");
	exit (EXIT_FAILURE);
}

void	executor(t_data **ms, t_cmd *cmd)
{
	if (cmd->cmd && (*ms)->hist == false)
	{
		if ((cmd->out_fd != -1 || cmd->in_fd != -1))
			open_redir(cmd);
		exec_here(ms, cmd);
		dup2((*ms)->stdin_fd, STDIN_FILENO);
	}
	else if (!cmd->cmd && (*ms)->hist)
		custom_exec(ms, cmd);
	else if (cmd && (*ms)->hist)
	{
		if ((cmd->out_fd != -1 || cmd->in_fd != -1))
			open_redir(cmd);
		execve(cmd->cmd, cmd->cmds, (*ms)->env);
		perror("smashell");
		exit (EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	prnt_ctrl(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	no_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	g_exit = 127;
	printf("smashell: command not found: ");
	while (cmd->cmds[++i])
		printf("%s ", cmd->cmds[i]);
	printf("\n");
}
