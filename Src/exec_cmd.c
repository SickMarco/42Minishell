/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:52:41 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/10 16:50:21 by mbozzi           ###   ########.fr       */
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
	ft_freelist(&lst);
	exec_cmd(ms, cmd);
	free_cmd(cmd);
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
	if (check_builtin(cmd_list) == false)
		executor(ms, cmd_list);
	exit(EXIT_FAILURE);
}

void	parent_pipe(t_data **ms, t_cmd *cmd_list, int *pipefd)
{
	int	status;

	status = 0;
	signal(SIGINT, prnt_ctrl);
	signal(SIGQUIT, prnt_ctrl);
	waitpid((*ms)->pid, &status, 0);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	if (check_builtin(cmd_list) == true)
		ft_builtin(ms, cmd_list);
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
	int			pipefd[2];
	static int	flag = 0;

	if (cmd_list == NULL)
		return ;
	if (cmd_list->next != NULL)
	{
		if (flag++ == 0)
			(*ms)->stdin_fd = dup(STDIN_FILENO);
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
	dup2((*ms)->stdin_fd, STDIN_FILENO);
	flag = 0;
}
