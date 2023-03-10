/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/10 14:50:33 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_builtin(t_data **ms, t_cmd *cmd)
{
	if (!cmd->cmds[0])
		return (false);
	else if (!ft_strncmp(cmd->cmds[0], "pwd", 4) && !cmd->cmds[1])
		ft_pwd(ms, cmd);
	else if (!ft_strncmp(cmd->cmds[0], "clear", 6))
		ft_clear();
	else if (!ft_strncmp(cmd->cmds[0], "cd", 3))
		ft_cd(cmd);
	else if (!ft_strncmp(cmd->cmds[0], "env", 4))
		ft_env(ms);
	else if (!ft_strncmp(cmd->cmds[0], "export", 6))
		ft_export(ms, cmd);
	else if (!ft_strncmp(cmd->cmds[0], "unset", 5))
		ft_unset(ms, cmd);
	else if (!ft_strncmp(cmd->cmds[0], "echo", 4))
		ft_echo(cmd);
	else
		return (false);
	return (true);
}

void	ft_pwd(t_data **ms, t_cmd *cmd)
{
	if (cmd->out_fd != -1)
		dup2(cmd->out_fd, STDOUT_FILENO);
	if (cmd->in_fd != -1)
		dup2(cmd->in_fd, STDIN_FILENO);
	(*ms)->pwd = getcwd(NULL, 0);
	getcwd((*ms)->pwd, sizeof((*ms)->pwd));
	printf("%s\n", (*ms)->pwd);
	free((*ms)->pwd);
	g_exit = 0;
}

void	ft_cd(t_cmd *cmd)
{
	if (cmd->out_fd != -1)
		dup2(cmd->out_fd, STDOUT_FILENO);
	if (cmd->in_fd != -1)
		dup2(cmd->in_fd, STDIN_FILENO);
	if (!cmd->cmds[1])
		chdir(getenv("HOME"));
	else if (chdir(cmd->cmds[1]) != 0)
	{
		g_exit = 1;
		return (perror("cd"));
	}
	g_exit = 0;
}

void	ft_echo(t_cmd *cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (cmd->out_fd != -1)
		dup2(cmd->out_fd, STDOUT_FILENO);
	if (cmd->in_fd != -1)
		dup2(cmd->in_fd, STDIN_FILENO);
	if (cmd->cmds[i])
	{
		while (cmd->cmds[++i])
		{
			if (!ft_strncmp(cmd->cmds[1], "-n", 2))
			{
				flag = 1;
				i++;
			}
			if (cmd->cmds[i + 1])
				printf("%s ", cmd->cmds[i]);
			else
				printf("%s", cmd->cmds[i]);
		}
		if (flag == 0)
			printf("\n");
	}
	g_exit = 0;
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
