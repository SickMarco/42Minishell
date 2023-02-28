/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/28 19:18:38 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_cmd(t_data **ms)
{
	int	i;

	i = -1;
	g_exit = 127;
	printf("smashell: command not found: ");
	while ((*ms)->cmd[++i])
		printf("%s ", (*ms)->cmd[i]);
	printf("\n");
}

void	prnt_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130;
	}
}

void	forker(t_data **ms, char *cmd)
{
	int			status;

	(*ms)->pid = fork();
	if ((*ms)->pid == -1)
		return (perror("fork"));
	if (!(*ms)->pid)
	{
		if (!access(cmd, F_OK | X_OK))
			execve(cmd, (*ms)->cmd, (*ms)->env);
		else
		{
			perror("smashell");
			exit (EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if ((*ms)->pid > 0)
	{
		waitpid((*ms)->pid, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
}

void	custom_exec(t_data **ms)
{
	struct stat	info;

	stat((*ms)->cmd[0], &info);
	if (S_ISDIR(info.st_mode))
	{
		g_exit = 126;
		printf("smashell: %s: Is a directory\n", (*ms)->cmd[0]);
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
	signal(SIGINT, prnt_ctrl);
	while ((*ms)->path[++i] && ft_strncmp((*ms)->cmd[0], ".", 1))
	{
		cmd = ft_strjoin((*ms)->path[i], (*ms)->cmd[0]);
		if (!access(cmd, F_OK))
			break ;
		free(cmd);
	}
	if (!(*ms)->path[i] || i == 0)
		custom_exec(ms);
	else
	{
		forker(ms, cmd);
		//free(cmd);
	}
	return ;
}
