/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:19:20 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/22 17:19:39 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser(t_data **ms)
{
	int	i;

	i = -1;
	if (!(*ms)->cmd[0])
		return ;
	else if (!ft_strncmp((*ms)->cmd[0], "pwd", 4) && !(*ms)->cmd[1])
		ft_pwd(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "clear", 6))
		ft_clear();
	else if (!ft_strncmp((*ms)->cmd[0], "cd", 2))
		ft_cd(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "env", 4))
		ft_env(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "export", 6))
		ft_export(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "unset", 5))
		ft_unset(ms);
	else if (!ft_strncmp((*ms)->cmd[0], "echo", 4))
		ft_echo(ms);
	else if (ft_strncmp((*ms)->cmd[0], "\0", 2))
	{
		printf("smashell: command not found: ");
		while ((*ms)->cmd[++i])
			printf("%s ", (*ms)->cmd[i]);
		printf("\n");
	}
}
