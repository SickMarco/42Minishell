/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:28:56 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/22 14:16:10 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_builder(t_data **ms)
{
	int	i;

	(*ms)->cmd = ft_split1((*ms)->input);
	ft_expander(ms);
	ft_parser(ms);
	i = -1;
	while ((*ms)->cmd[++i])
		free((*ms)->cmd[i]);
	free((*ms)->cmd);
}

int	check_input(t_data **ms)
{
	int	i;

	i = 0;
	if ((*ms)->cmd[1][i] == '=')
		return (0);
	while ((*ms)->cmd[1][i] && (ft_isalnum((*ms)->cmd[1][i])
		|| ft_isalpha((*ms)->cmd[1][i])))
		i++;
	if (!(*ms)->cmd[1][i] || (*ms)->cmd[1][i] != '=')
		return (0);
	i++;
	if (!(*ms)->cmd[1][i])
		return (0);
	while ((*ms)->cmd[1][i] && (ft_isalnum((*ms)->cmd[1][i])
		|| ft_isalpha((*ms)->cmd[1][i])))
		i++;
	if (!(*ms)->cmd[1][i])
		return (1);
	return (0);
}

void	user_dir_set(t_data **ms)
{
	(*ms)->user_dir = ft_strjoin("\033[0;36m", (*ms)->user);
	(*ms)->user_dir = ft_strjoin2((*ms)->user_dir, "@minishell: \033[0;37m");
}

void	free_for_all(t_data **ms)
{
	free((*ms)->user_dir);
	free((*ms)->exp);
	free((*ms)->input);
}