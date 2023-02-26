/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/26 20:40:29 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_builtin(t_data **ms)
{
	if (!(*ms)->cmd[0])
		return (false);
	else if (!ft_strncmp((*ms)->cmd[0], "pwd", 4) && !(*ms)->cmd[1])
		ft_pwd(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "clear", 6))
		ft_clear();
	else if (!ft_strncmp((*ms)->cmd[0], "cd", 3))
		ft_cd(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "env", 4))
		ft_env(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "export", 6))
		ft_export(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "unset", 5))
		ft_unset(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "echo", 4))
		ft_echo(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "$?", 3))
		printf("%d\n", g_exit);
	else
		return (false);
	return (true);
}

void	prnt_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130;
	}
}

void	no_cmd(t_data **ms)
{
	int	i;

	i = -1;
	printf("smashell: command not found: ");
	while ((*ms)->cmd[++i])
		printf("%s ", (*ms)->cmd[i]);
	printf("\n");
}

void	forker(t_data **ms, char *cmd)
{
	int	flag;

	(*ms)->pid = fork();
	if ((*ms)->pid == -1)
	{
		perror("fork");
		return ;
	}
	if (!(*ms)->pid)
	{
		if (access(cmd, F_OK) == 0)
			execve(cmd, (*ms)->cmd, (*ms)->env);
		else
			exit (1);
	}
	else if ((*ms)->pid > 0)
	{
		wait(&flag);
		if (WIFEXITED(flag))
			g_exit = WEXITSTATUS(flag);
	}
}

int	executor(t_data **ms)
{
	int		i;
	char	*cmd;

	i = -1;
	signal(SIGINT, prnt_ctrl);
	while ((*ms)->path[++i])
	{
		cmd = ft_strjoin((*ms)->path[i], (*ms)->cmd[0]);
		if (access(cmd, F_OK) == 0)
			break ;
		free(cmd);
	}
	if (!(*ms)->path[i])
	{
		g_exit = 127;
		return (1);
	}
	forker(ms, cmd);
	return (0);
}
