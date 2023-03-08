/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:39:04 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/08 15:11:15 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apex_exp(t_exp **exp, char *line)
{
	int		i;

	if (strchr(line, 39))
	{
		i = -1;
		(*exp)->cmds = ft_split(line, ' ');
		while ((*exp)->cmds[++i])
		{
			if (strchr((*exp)->cmds[i], 39) && strchr((*exp)->cmds[i], '$'))
			{
				(*exp)->trim = ft_strtrim((*exp)->cmds[i], "\"\'$");
				if (getenv((*exp)->trim))
				{
					(*exp)->var = ft_strdup(getenv((*exp)->trim));
					(*exp)->var = ft_strjoin3("\'", (*exp)->var, 1);
					(*exp)->var = ft_strjoin3((*exp)->var, "\'", 0);
					free((*exp)->cmds[i]);
					(*exp)->cmds[i] = (*exp)->var;
				}
				free((*exp)->trim);
			}
		}
	}
	return ;
}

void	exp_line(t_exp **exp)
{
	int		i;

	i = -1;
	while ((*exp)->cmds[++i])
	{
		if (strchr((*exp)->cmds[i], '$'))
		{
			(*exp)->trim = ft_strtrim((*exp)->cmds[i], "$\"");
			if (getenv((*exp)->trim))
			{
				(*exp)->var = ft_strdup(getenv((*exp)->trim));
				free((*exp)->cmds[i]);
				(*exp)->cmds[i] = (*exp)->var;
			}
			free((*exp)->trim);
		}
		else
		{
			(*exp)->trim = ft_strtrim((*exp)->cmds[i], "\"");
			free((*exp)->cmds[i]);
			(*exp)->cmds[i] = (*exp)->trim;
		}
	}
}

char	*multi_exp(t_exp **exp, char *line)
{
	char	*ret;
	int		i;

	i = 0;
	if (strchr(line, '\"') && strchr(line, '$') && strchr(line, '\''))
		apex_exp(exp, line);
	else
		(*exp)->cmds = ft_split(line, ' ');
	exp_line(exp);
	ret = ft_strjoin((*exp)->cmds[i], " ");
	while ((*exp)->cmds[++i])
	{
		ret = ft_strjoin2(ret, (*exp)->cmds[i]);
		if ((*exp)->cmds[i + 1])
			ret = ft_strjoin2(ret, " ");
	}
	i = -1;
	while ((*exp)->cmds[++i])
		free((*exp)->cmds[i]);
	free((*exp)->cmds);
	return (ret);
}

char	*ft_expander(char *line)
{
	t_exp	*exp;

	exp = ft_calloc(sizeof(t_exp), 1);
	line = exit_exp(line);
	if (strchr(line, '$') && !strchr(line, ' '))
	{
		exp->trim = ft_strtrim(line, "$\"");
		if (getenv(exp->trim))
		{
			exp->var = ft_strdup(getenv(exp->trim));
			free(line);
			line = exp->var;
		}
		else if (strchr(line, '\"') && strchr(line, '$') && strchr(line, '\''))
		{
			apex_exp(&exp, line);
			free(line);
			line = exp->cmds[0];
		}
		free(exp->trim);
	}
	else if (strchr(line, '$') && strchr(line, ' '))
		line = multi_exp(&exp, line);
	free(exp);
	return (line);
}
