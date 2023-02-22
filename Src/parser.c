/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:19:20 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/21 15:58:51 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser(t_data **ms)
{
	int	i;

	i = -1;
	if (ft_strncmp((*ms)->cmd[0], "pwd", 4) == 0 && !(*ms)->cmd[1])
		ft_pwd(ms);
	else if (ft_strncmp((*ms)->cmd[0], "clear", 6) == 0)
		ft_clear();
	else if (ft_strncmp((*ms)->cmd[0], "cd", 2) == 0)
		ft_cd(ms);
	else if (ft_strncmp((*ms)->cmd[0], "env", 4) == 0)
		ft_env();
	else if (ft_strncmp((*ms)->cmd[0], "export", 6) == 0)
		ft_export(ms);
	else if (ft_strncmp((*ms)->cmd[0], "\0", 2) != 0)
	{
		printf("smashell: command not found: ");
		while ((*ms)->cmd[++i])
			printf("%s ", (*ms)->cmd[i]);
		printf("\n");
	}
}
