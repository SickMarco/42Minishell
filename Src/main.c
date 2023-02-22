/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:19:29 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/21 18:17:31 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear(void)
{
	printf("\033[H\033[J\033[0;31m");
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

void	init_ms(t_data **ms)
{
	*ms = ft_calloc(sizeof(t_data), 1);
	(*ms)->exp = ft_calloc(sizeof(t_exp), 1);
	(*ms)->user = getenv("USER");
	(*ms)->home = getenv("HOME");
	user_dir_set(ms);
	ft_clear();
	printf("Welcome %s\n\n", (*ms)->user);
}

int	main(void)
{
	t_data	*ms;

	init_ms(&ms);
	while (1)
	{
		ms->input = readline(ms->user_dir);
		if (ms->input == NULL || ft_strncmp(ms->input, "exit", 5) == 0)
			break ;
		cmd_builder(&ms);
		if (ft_strlen(ms->input) != 0)
			add_history(ms->input);
		free(ms->input);
	}
	rl_clear_history();
	free_for_all(&ms);
	free(ms);
	exit (EXIT_SUCCESS);
}
