/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:53:53 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/12 19:42:28 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_input(t_cmd *cmd)
{
	int	i;

	i = 0;
	g_exit = 0;
	if (ft_isdigit(cmd->cmds[1][i]) || cmd->cmds[1][i] == '=')
	{
		write(STDERR_FILENO, "Export: Not valid identifier\n", 30);
		g_exit = 1;
		return (1);
	}
	while (cmd->cmds[1][i] && cmd->cmds[1][i] != '=')
	{
		if (!ft_isdigit(cmd->cmds[1][i]) && !ft_isalpha(cmd->cmds[1][i]))
		{
			write(STDERR_FILENO, "Export: Not valid identifier\n", 30);
			return (1);
		}
		i++;
	}
	if (!cmd->cmds[1][i] || cmd->cmds[1][i] != '=')
		return (1);
	i++;
	if (!cmd->cmds[1][i])
		return (1);
	return (0);
}

void	ft_env(t_data **ms)
{
	int	i;

	i = -1;
	while ((*ms)->env[++i])
		printf("%s\n", (*ms)->env[i]);
}

void	ft_export(t_data **ms, t_cmd *cmd)
{
	char	**new_env;
	int		i;

	i = 0;
	if (cmd->cmds[1] && !check_input(cmd))
	{
		while ((*ms)->env[i])
			i++;
		new_env = ft_calloc(sizeof(char *), (i + 2));
		i = -1;
		while ((*ms)->env[++i])
			new_env[i] = (*ms)->env[i];
		new_env[i] = ft_strdup(cmd->cmds[1]);
		free((*ms)->env);
		(*ms)->env = new_env;
		g_exit = 0;
	}
	else if (!(cmd->cmds[1]))
	{
		i = -1;
		while ((*ms)->env[++i])
			printf("declare -x %s\n", (*ms)->env[i]);
		g_exit = 0;
	}
}

void	ft_unset(t_data **ms, t_cmd *cmd)
{
	int		i;
	int		j;
	int		pos;
	char	**new_env;

	i = -1;
	j = 0;
	if (!cmd->cmds[1])
		return ;
	while ((*ms)->env[++i])
		if (!ft_strncmp((*ms)->env[i], cmd->cmds[1], ft_strlen(cmd->cmds[1])))
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

int	env_len(t_data **ms, int i)
{
	int	j;

	j = 0;
	while ((*ms)->env[i][j] && (*ms)->env[i][j] != '=')
		j++;
	return (j);
}
