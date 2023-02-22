/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:28:56 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/22 20:08:10 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrlc_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	mat_dup(t_data **ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	(*ms)->env = ft_calloc(sizeof(char *), (i + 1));
	i = -1;
	while (envp[++i])
		(*ms)->env[i] = ft_strdup(envp[i]);
}

void	cmd_builder(t_data **ms)
{
	int	i;

	(*ms)->cmd = ft_split1((*ms)->input);
	ft_expander(ms);
	ft_parser(ms);
	i = -1;
	while ((*ms)->cmd[++i])
		free((*ms)->cmd[i]);
	free((*ms)->cmd);
}

void	free_for_all(t_data **ms)
{
	int	i;

	i = -1;
	while ((*ms)->env[++i])
		free((*ms)->env[i]);
	free((*ms)->user_dir);
	free((*ms)->exp);
	free((*ms)->input);
	free((*ms)->env);
	free(*ms);
}
