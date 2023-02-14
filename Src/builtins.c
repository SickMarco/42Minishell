/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:33 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/14 19:48:53 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_data **data)
{
	(*data)->pwd = getcwd(NULL, 0);
	getcwd((*data)->pwd, sizeof((*data)->pwd));
	printf("%s\n", (*data)->pwd);
	free((*data)->pwd);
}

void	history(t_data **data)
{
	if (ft_strlen((*data)->input) != 0)
		add_history((*data)->input);
}