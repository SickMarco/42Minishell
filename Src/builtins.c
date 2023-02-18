/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/18 19:34:30 by mbozzi           ###   ########.fr       */
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
	char	**args;
	int		i;

	i = -1;
	args = ft_split((*ms)->trim, ' ');
	(*ms)->home = getenv("HOME");
	if (!args[1])
		chdir((*ms)-> home);
	else if (chdir(args[1]) != 0)
		perror("cd");
	while (args[++i])
		free(args[i]);
	free(args);
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
	char	**new;
	int		i;

	i = 0;
	new = ft_split((*ms)->trim, ' ');
	if (new[1] && check_input(new[1]))
	{
		while (environ[i])
			i++;
		new_env = ft_calloc(sizeof(char *), (i + 2));
		i = -1;
		while (environ[++i])
			new_env[i] = environ[i];
		new_env[i] = new[1];
		environ = new_env;
	}
	free(new);
}
