/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:52:44 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/27 17:20:59 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_exp2(t_data **ms, int i, int j, int x)
{
	char	*new;
	char	*exit;
	int		y;

	exit = ft_itoa2(g_exit);
	new = ft_calloc(sizeof(char), ft_strlen((*ms)->cmd[i]) - 2
			+ ft_strlen(exit) + 1);
	y = -1;
	j = -1;
	i = -1;
	while ((*ms)->cmd[x][++j] != '$')
		new[++i] = (*ms)->cmd[x][j];
	j++;
	while (exit[++y])
		new[++i] = exit[y];
	while ((*ms)->cmd[x][++j])
		new[++i] = (*ms)->cmd[x][j];
	free((*ms)->cmd[x]);
	(*ms)->cmd[x] = new;
	free(exit);
}

int	exit_exp(t_data **ms)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while ((*ms)->cmd[++i])
		if (ft_strchr((*ms)->cmd[i], '$'))
			break ;
	if (!(*ms)->cmd[i])
		return (1);
	while ((*ms)->cmd[i][j] != '$')
		j++;
	if ((*ms)->cmd[i][j + 1] != '?')
		return (1);
	exit_exp2(ms, i, j, i);
	return (0);
}
