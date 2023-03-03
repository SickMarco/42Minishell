/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:44:30 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/03 15:22:21 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dapex(t_data **ms, int i)
{
	int		j;

	j = 0;
	while ((*ms)->cmd[i][j] && (*ms)->cmd[i][j] != 34)
		j++;
	if (!(*ms)->cmd[i][j])
		return (0);
	while ((*ms)->cmd[i][j] && (*ms)->cmd[i][j] != 34)
		j++;
	if (!(*ms)->cmd[i][j])
		return (0);
	return (1);
}

int	check_apex(t_data **ms, int i)
{
	int		j;
	int		x;
	int		check;
	char	*new;

	j = -1;
	check = 0;
	if ((check_dapex(ms, i)) == 1)
		return (0);
	while ((*ms)->cmd[i][++j])
		if ((*ms)->cmd[i][j] == 39)
			check++;
	j = -1;
	if (check >= 2)
	{
		x = -1;
		new = ft_calloc(sizeof(char), (ft_strlen((*ms)->cmd[i])));
		while ((*ms)->cmd[i][++j])
			if ((*ms)->cmd[i][j] != 39)
				new[++x] = (*ms)->cmd[i][j];
		free((*ms)->cmd[i]);
		(*ms)->cmd[i] = new;
		return (1);
	}
	return (0);
}

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
	y = (*ms)->exp->var_len + x;
	while ((*ms)->exp->exp_var[++j])
		(*ms)->exp->exp_cmd[x++] = (*ms)->exp->exp_var[j];
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
	j = ft_strlen((*ms)->exp->var);
	while ((*ms)->env[++i])
		if (!ft_strncmp((*ms)->env[i], (*ms)->exp->var, env_len(ms, i)))
			break ;
	if (!(*ms)->env[i] || !(*ms)->env[i + 1])
		return (1);
	if ((*ms)->env[i][j] == '=')
		j++;
	(*ms)->exp->exp_var = ft_calloc(sizeof(char),
			ft_strlen((*ms)->env[i]) - j + 1);
	x = 0;
	while ((*ms)->env[i][j])
	{
		(*ms)->exp->exp_var[x] = (*ms)->env[i][j];
		x++;
		j++;
	}
	free((*ms)->exp->var);
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
	if (!(*ms)->cmd[i] || check_apex(ms, i) == 1
		|| !exit_exp(ms))
		return ;
	while ((*ms)->cmd[i][j] && (*ms)->cmd[i][j] != '$')
		j++;
	(*ms)->exp->start = j;
	while ((*ms)->cmd[i][j] && (*ms)->cmd[i][j] != ' ' &&
		(*ms)->cmd[i][j] != 34 && (*ms)->cmd[i][j] != 39)
		j++;
	(*ms)->exp->var_len = j - (*ms)->exp->start;
	(*ms)->exp->var = ft_calloc(sizeof(char), (*ms)->exp->var_len + 1);
	x = -1;
	while ((*ms)->exp->start++ < j)
		(*ms)->exp->var[++x] = (*ms)->cmd[i][(*ms)->exp->start];
	if (ft_find_var(ms) != 1)
		ft_cmd_exp(ms, i);
}
