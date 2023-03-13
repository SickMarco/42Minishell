/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:28:56 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/13 15:03:44 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrlc_handler(int sig)
{
	(void)sig;
	g_exit = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (!access(HERED, F_OK))
		unlink(HERED);
}

void	ft_clear(void)
{
	g_exit = 0;
	printf("\e[1;1H\e[2J");
	printf("\033[31m" );
	printf("\n░██████╗███╗░░░███╗░█████╗░░██████╗██╗░░\
██╗███████╗██╗░░░░░██╗░░░░░\n");
	printf("██╔════╝████╗░████║██╔══██╗██╔════╝██║░░██║\
██╔════╝██║░░░░░██║░░░░░\n");
	printf("╚█████╗░██╔████╔██║███████║╚█████╗░███████║\
█████╗░░██║░░░░░██║░░░░░\n");
	printf("░╚═══██╗██║╚██╔╝██║██╔══██║░╚═══██╗██╔══██║\
██╔══╝░░██║░░░░░██║░░░░░\n");
	printf("██████╔╝██║░╚═╝░██║██║░░██║██████╔╝██║░░██║\
███████╗███████╗███████╗\n");
	printf("╚═════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝\
╚══════╝╚══════╝╚══════╝\n\n\033[0;37m");
}

void	set_env(t_data **ms, char **envp)
{
	int	i;

	i = -1;
	(*ms)->path = ft_split(getenv("PATH"), ':');
	while ((*ms)->path[++i])
		(*ms)->path[i] = ft_strjoin2((*ms)->path[i], "/");
	i = 0;
	while (envp[i])
		i++;
	(*ms)->env = ft_calloc(sizeof(char *), (i + 1));
	i = -1;
	while (envp[++i])
		(*ms)->env[i] = ft_strdup(envp[i]);
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
