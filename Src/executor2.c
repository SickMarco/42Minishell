/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:24:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/08 14:45:30 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_fork(t_data **ms, char *cmd)
{
	int		status;
	char	**cmds;

	cmds = ft_calloc(sizeof(char *), 2);
	cmds[0] = ft_strdup(cmd);
	(*ms)->fd = open(HERED, O_RDONLY);
	(*ms)->pid = fork();
	if (!(*ms)->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2((*ms)->fd, STDIN_FILENO);
		close((*ms)->fd);
		execve(cmd, cmds, NULL);
		perror("smashell");
		exit (EXIT_FAILURE);
	}
	else if ((*ms)->pid > 0)
	{
		close((*ms)->fd);
		waitpid((*ms)->pid, &status, 0);
	}
	free(cmds[0]);
	free(cmds);
	return ;
}
