/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/18 18:11:34 by mbozzi           ###   ########.fr       */
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

void	ft_history(t_data **ms)
{
	if (ft_strlen((*ms)->input) != 0)
		add_history((*ms)->input);
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
