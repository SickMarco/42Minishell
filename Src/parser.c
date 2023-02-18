/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:19:20 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/18 19:25:58 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser(t_data **ms)
{
	if (ft_strncmp((*ms)->trim, "pwd", 4) == 0)
		ft_pwd(ms);
	else if (ft_strncmp((*ms)->trim, "clear", 6) == 0)
		ft_clear(ms);
	else if (ft_strncmp((*ms)->trim, "cd", 2) == 0)
		ft_cd(ms);
	else if (ft_strncmp((*ms)->trim, "env", 4) == 0)
		ft_env();
	else if (ft_strncmp((*ms)->trim, "export", 6) == 0)
		ft_export(ms);
	else if (ft_strncmp((*ms)->trim, "\0", 2) != 0)
		ft_printf("smashell: command not found: %s\n", (*ms)->trim);
}
