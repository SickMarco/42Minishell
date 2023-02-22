/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:53:53 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/22 16:55:06 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data **ms)
{
	int	i;

	i = -1;
	while ((*ms)->env[++i])
		printf("%s\n", (*ms)->env[i]);
}

void	ft_export(t_data **ms)
{
	char	**new_env;
	int		i;

	i = 0;
	if ((*ms)->cmd[1] && check_input(ms))
	{
		while ((*ms)->env[i])
			i++;
		new_env = ft_calloc(sizeof(char *), (i + 2));
		i = -1;
		while ((*ms)->env[++i])
			new_env[i] = (*ms)->env[i];
		new_env[i] = ft_strdup((*ms)->cmd[1]);
		i = -1;
		free((*ms)->env);
		(*ms)->env = new_env;
	}
}

void	ft_unset(t_data **ms)
{
	int		i;
	int		j;
	int		pos;
	char	**new_env;

	i = -1;
	j = 0;
	if (!(*ms)->cmd[1])
		return ;
	while ((*ms)->env[++i])
		if (!ft_strncmp((*ms)->env[i], (*ms)->cmd[1], ft_strlen((*ms)->cmd[1])))
			break ;
	pos = i;
	if (!(*ms)->env[i])
		return ;
	while ((*ms)->env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i);
	i = -1;
	while ((*ms)->env[++i])
		if (i != pos)
			new_env[j++] = (*ms)->env[i];
	free((*ms)->env[pos]);
	free((*ms)->env);
	(*ms)->env = new_env;
}
