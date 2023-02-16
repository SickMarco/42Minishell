/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:19:29 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/16 12:17:53 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	welcome_msg(t_data **data)
{
	printf("\033[H\033[J\033[0;31m");
	printf("\n░██████╗███╗░░░███╗░█████╗░░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n");
	printf("██╔════╝████╗░████║██╔══██╗██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n");
	printf("╚█████╗░██╔████╔██║███████║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n");
	printf("░╚═══██╗██║╚██╔╝██║██╔══██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n");
	printf("██████╔╝██║░╚═╝░██║██║░░██║██████╔╝██║░░██║███████╗███████╗███████╗\n");
	printf("╚═════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\033[0;37m\nWelcome %s\n\n", (*data)->user);
}

int	main(void)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	data->user = getenv("USER");
	welcome_msg(&data);
	while (1)
	{
		data->input = readline("$>");
		data->trimmed = ft_strtrim(data->input, " ");
		if (data->input == NULL || ft_strncmp(data->trimmed, "exit", 5) == 0)
			break ;
		ft_parser(&data);
		ft_history(&data);
		free(data->input);
		free(data->trimmed);
	}
	free(data->input);
	free(data->trimmed);
	free(data);
	exit (EXIT_SUCCESS);
}
