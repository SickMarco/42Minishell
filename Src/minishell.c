/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:19:29 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/18 19:09:49 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear(t_data **ms)
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
╚══════╝╚══════╝╚══════╝\n");
	printf("\033[0;37m\nWelcome %s\n\n", (*ms)->user);
}

int	main(void)
{
	t_data	*ms;

	ms = ft_calloc(sizeof(t_data), 1);
	ms->user = getenv("USER");
	ft_clear(&ms);
	while (1)
	{
		ms->trim = ft_strtrim(ms->input = readline("\033[0;36m$>\033[0m"), " ");
		if (ms->input == NULL || ft_strncmp(ms->trim, "exit", 5) == 0)
			break ;
		ft_parser(&ms);
		if (ft_strlen(ms->input) != 0)
			add_history(ms->input);
		free(ms->input);
		free(ms->trim);
	}
	rl_clear_history();
	free(ms->input);
	free(ms->trim);
	free(ms);
	exit (EXIT_SUCCESS);
}
