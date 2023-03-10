/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:19:29 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/10 14:59:29 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit;

void	init_ms(t_data **ms, char **envp, int ac, char	**av)
{
	(void)ac;
	(void)av;
	g_exit = 0;
	*ms = ft_calloc(sizeof(t_data), 1);
	(*ms)->exp = ft_calloc(sizeof(t_exp), 1);
	(*ms)->prompt = ft_strjoin("\033[0;36m", getenv("USER"));
	(*ms)->prompt = ft_strjoin2((*ms)->prompt, "@minishell: \033[0;37m");
	set_env(ms, envp);
	ft_clear();
	printf("Welcome %s\n\n", getenv("USER"));
}

static int	is_valid_input(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] > 33 && s[i] != 127)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*ms;

	init_ms(&ms, envp, ac, av);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrlc_handler);
		ms->hist = true;
		ms->input = readline(ms->prompt);
		if (ms->input == NULL || !ft_strncmp(ms->input, "exit", 5))
		{
			printf("exit\n");
			break ;
		}
		if (is_valid_input(ms->input))
			cmd_builder(&ms);
		if (ft_strlen(ms->input) != 0 && ms->hist == true)
			add_history(ms->input);
		free(ms->input);
	}
	rl_clear_history();
	free_for_all(&ms);
	exit (EXIT_SUCCESS);
}
