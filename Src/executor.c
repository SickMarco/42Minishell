/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:17 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/24 18:04:03 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_ctrl(int sig)
{
	(void)sig;
	printf("\n");
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

int	child_proc(t_data **ms)
{
	int		i;
	char	*cmd;

	i = -1;
	while ((*ms)->path[++i])
	{
		cmd = ft_strjoin((*ms)->path[i], (*ms)->cmd[0]);
		if (access(cmd, F_OK) == 0)
			break ;
		free(cmd);
	}
	if (access(cmd, F_OK) == 0)
		execve(cmd, (*ms)->cmd, (*ms)->env);
	else
		return (1);
	return (0);
}

void	executor(t_data **ms)
{
	(*ms)->pid = fork();
	signal(SIGINT, child_ctrl);
	if ((*ms)->pid == -1)
	{
		perror("fork");
		return ;
	}
	if ((*ms)->pid == 0)
	{
		if (child_proc(ms))
			no_cmd(ms);
	}
	else
		waitpid((*ms)->pid, NULL, 0);
}
