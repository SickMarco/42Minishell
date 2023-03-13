/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/13 18:44:07 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	custom_exec(t_data **ms, t_cmd *cmd)
{
	struct stat	info;

	if (!stat(cmd->cmds[0], &info) && (S_ISDIR(info.st_mode)))
	{
		g_exit = 126;
		printf("smashell: %s: Is a directory\n", cmd->cmds[0]);
	}
	else if (!access(cmd->cmds[0], X_OK))
	{
		execve(cmd->cmds[0], cmd->cmds, (*ms)->env);
		perror("smashell");
		free_for_all2(ms);
		exit(EXIT_FAILURE);
	}
	else if (!access(cmd->cmds[0], F_OK))
	{
		g_exit = 126;
		perror("smashell");
	}
	else
		no_cmd(cmd);
	free_for_all2(ms);
	exit(g_exit);
}

void	exec_here(t_data **ms, t_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = -1;
	while (cmd->cmds[++i] && ft_strncmp(cmd->cmds[i], "<<", 3))
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (cmd->cmds[++i] && ft_strncmp(cmd->cmds[i], "<<", 3))
		tmp[i] = ft_strdup(cmd->cmds[i]);
	i = -1;
	while (cmd->cmds[++i])
		free(cmd->cmds[i]);
	free(cmd->cmds);
	cmd->cmds = tmp;
	if (!access(HERED, F_OK))
	{
		(*ms)->fd = open(HERED, O_RDONLY);
		dup2((*ms)->fd, STDIN_FILENO);
		close((*ms)->fd);
		execve(cmd->cmd, cmd->cmds, (*ms)->env);
		perror("smashell");
	}
}

void	executor(t_data **ms, t_cmd *cmd)
{
	if ((cmd->out_fd != -1 || cmd->in_fd != -1))
		open_redir(cmd);
	if (cmd->cmd && (*ms)->hist == false)
		exec_here(ms, cmd);
	else if (!cmd->cmd && (*ms)->hist)
		custom_exec(ms, cmd);
	else if (cmd && (*ms)->hist)
	{
		execve(cmd->cmd, cmd->cmds, (*ms)->env);
		perror("smashell");
	}
	close_redir(ms, cmd);
	free_for_all2(ms);
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
