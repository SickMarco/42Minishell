/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:52:41 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/09 17:49:18 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_pipe(t_data **ms, t_cmd *cmd_list, int pipefd[2])
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	if (ft_builtin(ms, cmd_list) == false)
		executor(ms, cmd_list);
	exit(EXIT_FAILURE);
}

void	parent_pipe(t_data **ms, t_cmd *cmd_list, int *pipefd)
{
	int	status;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, prnt_ctrl);
	signal(SIGQUIT, prnt_ctrl);
	close(pipefd[0]);
	waitpid((*ms)->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = WTERMSIG(status) + 128;
	exec_cmd(ms, cmd_list->next);
}

void	last_cmd(t_data **ms, t_cmd *cmd_list)
{
	int	status;

	(*ms)->pid = fork();
	if ((*ms)->pid == -1)
		return (perror("fork"));
	else if ((*ms)->pid == 0)
		executor(ms, cmd_list);
	else
	{
		signal(SIGINT, prnt_ctrl);
		signal(SIGQUIT, prnt_ctrl);
		waitpid((*ms)->pid, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = WTERMSIG(status) + 128;
	}
}

void	exec_cmd(t_data **ms, t_cmd *cmd_list)
{
	int	pipefd[2];

	if (cmd_list == NULL)
		return ;
	if (cmd_list->next != NULL)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"));
		(*ms)->pid = fork();
		if ((*ms)->pid == -1)
			return (perror("fork"));
		else if (!(*ms)->pid)
			child_pipe(ms, cmd_list, pipefd);
		else
			parent_pipe(ms, cmd_list, pipefd);
	}
	else if (ft_builtin(ms, cmd_list) == false)
		last_cmd(ms, cmd_list);
}
