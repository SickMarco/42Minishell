/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:19:29 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/27 17:27:38 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit;

void	init_ms(t_data **ms, char **envp, int ac, char	**av)
{
	int	i;

	i = -1;
	(void)ac;
	(void)av;
	*ms = ft_calloc(sizeof(t_data), 1);
	(*ms)->exp = ft_calloc(sizeof(t_exp), 1);
	g_exit = 0;
	(*ms)->user = getenv("USER");
	(*ms)->home = getenv("HOME");
	(*ms)->path = ft_split(getenv("PATH"), ':');
	while ((*ms)->path[++i])
		(*ms)->path[i] = ft_strjoin2((*ms)->path[i], "/");
	mat_dup(ms, envp);
	(*ms)->user_dir = ft_strjoin("\033[0;36m", (*ms)->user);
	(*ms)->user_dir = ft_strjoin2((*ms)->user_dir, "@minishell: \033[0;37m");
	(*ms)->pid = 0;
	ft_clear();
	printf("Welcome %s\n\n", (*ms)->user);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*ms;

	init_ms(&ms, envp, ac, av);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrlc_handler);
		ms->input = readline(ms->user_dir);
		if (ms->input == NULL || ft_strncmp(ms->input, "exit", 5) == 0)
		{
			printf("exit\n");
			break ;
		}
		cmd_builder(&ms);
		if (ft_strlen(ms->input) != 0)
			add_history(ms->input);
		free(ms->input);
	}
	rl_clear_history();
	free_for_all(&ms);
	exit (EXIT_SUCCESS);
}
