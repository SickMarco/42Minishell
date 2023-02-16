/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/15 18:53:07 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser(t_data **data)
{
	if (ft_strncmp((*data)->trimmed, "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp((*data)->trimmed, "clear", 6) == 0)
		ft_clear(data);
	else if (ft_strncmp((*data)->trimmed, "cd", 2) == 0)
		ft_cd(data);
	else
		ft_printf("smashell: command not found: %s\n", (*data)->trimmed);
}

void	ft_pwd(t_data **data)
{
	(*data)->pwd = getcwd(NULL, 0);
	getcwd((*data)->pwd, sizeof((*data)->pwd));
	printf("%s\n", (*data)->pwd);
	free((*data)->pwd);
}

void	ft_history(t_data **data)
{
	if (ft_strlen((*data)->input) != 0)
		add_history((*data)->input);
}

void	ft_clear(t_data **data)
{
	welcome_msg(data);
}

void	ft_cd(t_data **data)
{
	char	**args;
	int		i;

	i = -1;
	args = ft_split((*data)->trimmed, ' ');
	if (chdir(args[1]) != 0)
		perror("cd");
	while (args[++i])
		free(args[i]);
	free(args);
}
