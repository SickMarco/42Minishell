/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:28:56 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/10 12:55:11 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_data **ms, t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = -1;
	while ((*ms)->cmd[++i])
		free((*ms)->cmd[i]);
	free((*ms)->cmd);
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	cmd = NULL;
}

void	cmd_builder(t_data **ms)
{
	int		i;
	t_cmd	*cmd;
	t_list	*lst;

	if (!access(HERED, F_OK))
		unlink(HERED);
	if (ft_strncmp((*ms)->input, "\n", 2) != -10)
	{
		ft_readifyouneed(&((*ms)->input), ms);
		(*ms)->cmd = ft_split1((*ms)->input);
		i = -1;
		while ((*ms)->cmd[++i])
			(*ms)->cmd[i] = ft_expander((*ms)->cmd[i]);
		lst = ft_subsplit((*ms)->cmd);
		cmd = create_cmdlst(&lst, *ms);
		exec_cmd(ms, cmd);
		//free_cmd(ms, cmd);
	}
	return ;
}

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
	write(STDOUT_FILENO, "\e[1;1H\e[2J", 12);
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
	free((*ms)->exp);
	free((*ms)->input);
	free((*ms)->env);
	free(*ms);
	if (!access(HERED, F_OK))
		unlink(HERED);
}
