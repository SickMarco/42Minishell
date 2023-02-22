/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/21 15:07:27 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data **ms)
{
	(*ms)->pwd = getcwd(NULL, 0);
	getcwd((*ms)->pwd, sizeof((*ms)->pwd));
	printf("%s\n", (*ms)->pwd);
	free((*ms)->pwd);
}

void	ft_cd(t_data **ms)
{
	int		i;

	i = -1;
	if (!(*ms)->cmd[1])
		chdir((*ms)-> home);
	else if (chdir((*ms)->cmd[1]) != 0)
		perror("cd");
}

void	ft_env(void)
{
	int	i;

	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);
}

void	ft_export(t_data **ms)
{
	char	**new_env;
	int		i;

	i = 0;
	if ((*ms)->cmd[1] && check_input(ms))
	{
		while (environ[i])
			i++;
		new_env = ft_calloc(sizeof(char *), (i + 2));
		i = -1;
		while (environ[++i])
			new_env[i] = environ[i];
		new_env[i] = ft_strdup((*ms)->cmd[1]);
		free(environ);
		environ = new_env;
	}
}
