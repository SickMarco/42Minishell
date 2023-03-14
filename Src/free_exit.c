/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:23:13 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/14 18:28:13 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_data **ms)
{
	int		cexit;
	int		i;

	i = 0;
	cexit = 0;
	(*ms)->cmd = ft_split((*ms)->input, ' ');
	while (ft_isdigit((*ms)->cmd[1][i]))
		i++;
	if ((*ms)->cmd[1][i])
	{
		printf("smashell: exit: %s: numeric argument required\n", (*ms)->cmd[1]);
		cexit = 2;
	}
	else if ((*ms)->cmd[2])
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 26);
		g_exit = 1;
		free_matrix((*ms)->cmd);
		return ;
	}
	else
		cexit = ft_atoi_long((*ms)->cmd[1]);
	free_matrix((*ms)->cmd);
	free_for_all(ms);
	exit (cexit);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	free_for_all(t_data **ms)
{
	int	i;

	i = -1;
	while ((*ms)->env[++i])
		free((*ms)->env[i]);
	i = -1;
	while ((*ms)->path[++i])
		free((*ms)->path[i]);
	free((*ms)->path);
	free((*ms)->prompt);
	free((*ms)->input);
	free((*ms)->env);
	free(*ms);
}

void	free_for_all2(t_data **ms)
{
	int	i;

	i = -1;
	while ((*ms)->env[++i])
		free((*ms)->env[i]);
	i = -1;
	while ((*ms)->path[++i])
		free((*ms)->path[i]);
	free((*ms)->path);
	free((*ms)->prompt);
	free((*ms)->input);
	free((*ms)->env);
	free_cmd((*ms)->cmd_list);
	free(*ms);
}

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->cmd != NULL)
			free(cmd->cmd);
		i = -1;
		while (cmd->cmds[++i])
			free(cmd->cmds[i]);
		free(cmd->cmds);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}
