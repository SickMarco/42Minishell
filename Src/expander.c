/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:44:30 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/20 19:55:44 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmd_exp(t_data **ms, int i)
{
	int	j;
	int	x;
	int	y;
	int	len_exp;

	j = -1;
	x = -1;
	len_exp = ft_strlen((*ms)->exp->exp_var);
	(*ms)->exp->exp_cmd = ft_calloc(sizeof(char),
			(ft_strlen((*ms)->cmd[i]) - (*ms)->exp->var_len + len_exp + 2));
	while ((*ms)->cmd[i][++x] && (*ms)->cmd[i][x] != '$')
		(*ms)->exp->exp_cmd[x] = (*ms)->cmd[i][x];
	y = x;
	while ((*ms)->exp->exp_var[++j])
		(*ms)->exp->exp_cmd[x++] = (*ms)->exp->exp_var[j];
	while ((*ms)->cmd[i][y] && (*ms)->cmd[i][y] != ' ')
		y++;
	if ((*ms)->cmd[i][y])
		while ((*ms)->cmd[i][y])
			(*ms)->exp->exp_cmd[x++] = (*ms)->cmd[i][y++];
	free((*ms)->cmd[i]);
	free((*ms)->exp->exp_var);
	(*ms)->cmd[i] = (*ms)->exp->exp_cmd;
}

int	ft_find_var(t_data **ms)
{
	int	i;
	int	j;
	int	x;

	i = -1;
	while (environ[++i])
		if (ft_strncmp(environ[i], (*ms)->exp->var,
				ft_strlen((*ms)->exp->var) - 1) == 0)
			break ;
	if (!environ[i])
		return (1);
	j = ft_strlen((*ms)->exp->var);
	if (environ[i][j] == '=')
		j++;
	(*ms)->exp->exp_var = ft_calloc(sizeof(char),
			ft_strlen(environ[i]) - j + 1);
	x = 0;
	while (environ[i][j])
	{
		(*ms)->exp->exp_var[x] = environ[i][j];
		x++;
		j++;
	}
	return (0);
}

void	ft_expander(t_data **ms)
{
	int		i;
	int		j;
	int		x;

	i = -1;
	j = 0;
	while ((*ms)->cmd[++i])
		if (ft_strchr((*ms)->cmd[i], '$'))
			break ;
	if (!(*ms)->cmd[i])
		return ;
	while ((*ms)->cmd[i][j] && (*ms)->cmd[i][j] != '$')
		j++;
	(*ms)->exp->start = j;
	while ((*ms)->cmd[i][j] && (*ms)->cmd[i][j] != ' ')
		j++;
	(*ms)->exp->var_len = j - (*ms)->exp->start;
	(*ms)->exp->var = ft_calloc(sizeof(char), j - (*ms)->exp->start + 1);
	x = -1;
	while ((*ms)->exp->start++ < j)
		(*ms)->exp->var[++x] = (*ms)->cmd[i][(*ms)->exp->start];
	if (ft_find_var(ms) != 1)
		ft_cmd_exp(ms, i);
	free((*ms)->exp->var);
}
