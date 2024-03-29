/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/13 15:14:00 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_builtin(t_data **ms, t_cmd *cmd)
{
	if ((cmd->out_fd != -1 || cmd->in_fd != -1) && check_builtin(cmd) == true)
		open_redir(cmd);
	if (!cmd->cmds[0])
		return (false);
	else if (!ft_strncmp(cmd->cmds[0], "pwd", 4))
		ft_pwd(ms);
	else if (!ft_strncmp(cmd->cmds[0], "clear", 6))
		ft_clear();
	else if (!ft_strncmp(cmd->cmds[0], "cd", 3))
		ft_cd(ms, cmd);
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
	close_redir(ms, cmd);
	return (true);
}

void	ft_pwd(t_data **ms)
{
	(*ms)->pwd = getcwd(NULL, 0);
	getcwd((*ms)->pwd, sizeof((*ms)->pwd));
	printf("%s\n", (*ms)->pwd);
	free((*ms)->pwd);
	g_exit = 0;
}

void	ft_cd(t_data **ms, t_cmd *cmd)
{
	if ((*ms)->pipe == 0)
	{
		if (!cmd->cmds[1])
		{
			g_exit = 0;
			chdir(getenv("HOME"));
		}
		else if (cmd->cmds[2])
		{
			g_exit = 1;
			write(STDERR_FILENO, "cd : Too many arguments\n", 25);
		}
		else if (chdir(cmd->cmds[1]) != 0)
		{
			g_exit = 1;
			return (perror("cd"));
		}
		else
			g_exit = 0;
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
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

bool	check_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmds[0], "pwd", 4)
		|| !ft_strncmp(cmd->cmds[0], "clear", 6)
		|| !ft_strncmp(cmd->cmds[0], "cd", 3)
		|| !ft_strncmp(cmd->cmds[0], "env", 4)
		|| !ft_strncmp(cmd->cmds[0], "export", 6)
		|| !ft_strncmp(cmd->cmds[0], "unset", 5)
		|| !ft_strncmp(cmd->cmds[0], "echo", 4))
		return (true);
	return (false);
}
