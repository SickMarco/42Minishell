/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:36:05 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/08 15:19:13 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exit_exp2(char *line, int stop)
{
	char	*new;
	char	*exit;
	int		y;
	int		i;
	int		x;

	y = -1;
	i = -1;
	exit = ft_itoa2(g_exit);
	new = ft_calloc(sizeof(char), ft_strlen(line) - 2
			+ ft_strlen(exit) + 1);
	while (++y < stop)
		new[++i] = line[y];
	x = -1;
	while (exit[++x])
		new[++i] = exit[x];
	while (line[y] && line[y] != ' ' && line[y] != 34 && line[y] != 39)
		y++;
	if (line[y])
		while (line[y])
			new[++i] = line[y++];
	free(exit);
	return (new);
}

char	*exit_exp(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	if (ft_strchr(line, '$'))
	{
		while (line[++i])
		{
			if (line[i] == '$' && line[i + 1] == '?')
			{
				tmp = exit_exp2(line, i);
				free(line);
				return (tmp);
			}
		}
	}
	return (line);
}
