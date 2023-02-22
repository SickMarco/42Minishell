/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/22 17:37:45 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data **ms)
{
	(*ms)->pwd = getcwd(NULL, 0);
	getcwd((*ms)->pwd, sizeof((*ms)->pwd));
	printf("%s\n", (*ms)->pwd);
	free((*ms)->pwd);
}

void	ft_cd(t_data **ms)
{
	int		i;

	i = -1;
	if (!(*ms)->cmd[1])
		chdir((*ms)-> home);
	else if (chdir((*ms)->cmd[1]) != 0)
		perror("cd");
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

}
