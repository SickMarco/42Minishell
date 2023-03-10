/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/10 14:55:34 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_builder(t_data **ms)
{
	int		i;
	t_cmd	*cmd;
	t_list	*lst;

	if (!access(HERED, F_OK))
		unlink(HERED);
	ft_readifyouneed(&((*ms)->input), ms);
	(*ms)->cmd = ft_split1((*ms)->input);
	i = -1;
	while ((*ms)->cmd[++i])
		(*ms)->cmd[i] = ft_expander((*ms)->cmd[i]);
	ft_trimone((*ms)->cmd);
	lst = ft_subsplit((*ms)->cmd);
	cmd = create_cmdlst(&lst, *ms);
	exec_cmd(ms, cmd);
	free_cmd(cmd);
	return ;
}

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
		no_cmd(cmd);
	exit(g_exit);
}

void	exec_here(t_data **ms, t_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = -1;
	(*ms)->stdin_fd = dup(STDIN_FILENO);
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
	int	i;

	i = -1;
	if (cmd->cmd && (*ms)->hist == false)
	{
		if (cmd->out_fd != -1)
			dup2(cmd->out_fd, STDOUT_FILENO);
		if (cmd->in_fd != -1)
			dup2(cmd->in_fd, STDIN_FILENO);
		exec_here(ms, cmd);
		dup2((*ms)->stdin_fd, STDIN_FILENO);
	}
	else if (!cmd->cmd && (*ms)->hist)
		custom_exec(ms, cmd);
	else if (cmd && (*ms)->hist)
	{
		if (cmd->out_fd != -1)
			dup2(cmd->out_fd, STDOUT_FILENO);
		if (cmd->in_fd != -1)
			dup2(cmd->in_fd, STDIN_FILENO);
		execve(cmd->cmd, cmd->cmds, (*ms)->env);
		perror("smashell");
		exit (EXIT_FAILURE);
	}
	return ;
}

void	prnt_ctrl(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}
