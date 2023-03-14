/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:52:41 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/13 19:53:31 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_builder(t_data **ms)
{
	int		i;

	if (!access(HERED, F_OK))
		unlink(HERED);
	ft_readifyouneed(&((*ms)->input), ms);
	(*ms)->cmd = ft_split1((*ms)->input);
	i = -1;
	while ((*ms)->cmd[++i])
		(*ms)->cmd[i] = ft_expander((*ms)->cmd[i]);
//	ft_trimone((*ms)->cmd);
	(*ms)->list = ft_subsplit((*ms)->cmd);
//trimone dopo subsplit, trasformarlo per lavorare con le liste
	(*ms)->cmd_list = create_cmdlst((*ms)->list, *ms);
	if ((*ms)->cmd_list == NULL && (*ms)->hist)
		perror("Wrong syntax");
	if (g_exit == 1234)
		g_exit = 1;
	else
		exec_cmd(ms, (*ms)->cmd_list);
	free_cmd((*ms)->cmd_list);
	return ;
}

void	child_pipe(t_data **ms, t_cmd *cmd_list, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	if (ft_builtin(ms, cmd_list) == false)
		executor(ms, cmd_list);
	exit(EXIT_SUCCESS);
}

void	parent_pipe(t_data **ms, t_cmd *cmd_list, int *pipefd)
{
	int	status;

	status = 0;
	(*ms)->pipe = 1;
	signal(SIGINT, prnt_ctrl);
	signal(SIGQUIT, prnt_ctrl);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	waitpid((*ms)->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = WTERMSIG(status) + 128;
	exec_cmd(ms, cmd_list->next);
}

void	single_cmd(t_data **ms, t_cmd *cmd_list)
{
	int	status;

	status = 0;
	(*ms)->pid = fork();
	if ((*ms)->pid == -1)
		return (perror("fork"));
	else if (!(*ms)->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		executor(ms, cmd_list);
	}
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
	int			pipefd[2];

	if (!cmd_list)
		return ;
	if (cmd_list->next)
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
		single_cmd(ms, cmd_list);
	(*ms)->pipe = 0;
	dup2((*ms)->stdin_fd, STDIN_FILENO);
}
