/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:28:56 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/20 13:02:45 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_input(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (0);
	while (arg[i] && (ft_isalnum(arg[i]) || ft_isalpha(arg[i])))
		i++;
	if (!arg[i] || arg[i] != '=')
		return (0);
	i++;
	if (!arg[i])
		return (0);
	while (arg[i] && (ft_isalnum(arg[i]) || ft_isalpha(arg[i])))
		i++;
	if (!arg[i])
		return (1);
	return (0);
}

void	user_dir_set(t_data **ms)
{
	(*ms)->user_dir = ft_strjoin("\033[0;36m", (*ms)->user);
	(*ms)->user_dir = ft_strjoin2((*ms)->user_dir, "@minishell: \033[0;37m");
}
