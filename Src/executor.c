/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/06 15:58:10 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prnt_ctrl(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	forker(t_data **ms, char *cmd)
{
	int			status;

	(*ms)->pid = fork();
	if ((*ms)->pid == -1)
		return (perror("fork"));
	if (!(*ms)->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(cmd, (*ms)->cmd, (*ms)->env);
		perror("smashell");
		exit (EXIT_FAILURE);
	}
	else if ((*ms)->pid > 0)
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

void	custom_exec(t_data **ms)
{
	struct stat	info;

	if (!stat((*ms)->cmd[0], &info) && (S_ISDIR(info.st_mode)))
	{
		g_exit = 126;
		printf("smashell: %s: Is a directory\n", (*ms)->cmd[0]);
		return ;
	}
	else if (!access((*ms)->cmd[0], X_OK))
		forker(ms, (*ms)->cmd[0]);
	else if (!access((*ms)->cmd[0], F_OK))
	{
		g_exit = 126;
		perror("smashell");
	}
	else
		no_cmd(ms);
	return ;
}

void	executor(t_data **ms)
{
	int			i;
	char		*cmd;

	i = -1;
	while ((*ms)->path[++i] && ft_strncmp((*ms)->cmd[0], ".", 1))
	{
		cmd = ft_strjoin((*ms)->path[i], (*ms)->cmd[0]);
		if (!access(cmd, F_OK))
			break ;
		free(cmd);
	}
	if (cmd && !access(HERED, F_OK))
		heredoc_fork(ms, cmd);
	else if ((!(*ms)->path[i] || i == 0) && (*ms)->hist)
		custom_exec(ms);
	else if (cmd && (*ms)->hist)
		forker(ms, cmd);
	if (!access(HERED, F_OK))
		unlink(HERED);
	return ;
}
