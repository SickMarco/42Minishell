/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/28 18:26:46 by mbozzi           ###   ########.fr       */
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
	else
		return (false);
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

void	ft_cd(t_data **ms)
{
	if (!(*ms)->cmd[1])
		chdir((*ms)-> home);
	else if (chdir((*ms)->cmd[1]) != 0)
	{
		g_exit = 1;
		return (perror("cd"));
	}
	g_exit = 0;
}

void	ft_echo(t_data **ms)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if ((*ms)->cmd[i])
	{
		while ((*ms)->cmd[++i])
		{
			if (!ft_strncmp((*ms)->cmd[1], "-n", 2))
			{
				flag = 1;
				i++;
			}
			if ((*ms)->cmd[i + 1])
				printf("%s ", (*ms)->cmd[i]);
			else
				printf("%s", (*ms)->cmd[i]);
		}
		if (flag == 0)
			printf("\n");
	}
	g_exit = 0;
}
