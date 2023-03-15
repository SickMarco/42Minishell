/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:39:04 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/13 17:58:39 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apex_exp(t_exp **exp, char *line)
{
	int		i;
	char	*trim;

	if (strchr(line, 39))
	{
		i = -1;
		(*exp)->cmds = ft_split(line, ' ');
		while ((*exp)->cmds[++i])
		{
			if (strchr((*exp)->cmds[i], 39) && strchr((*exp)->cmds[i], '$'))
			{
				trim = ft_strtrim((*exp)->cmds[i], "\"\'$");
				if (getenv(trim))
				{
					(*exp)->var = ft_strdup(getenv(trim));
					(*exp)->var = ft_strjoin3("\'", (*exp)->var, 1);
					(*exp)->var = ft_strjoin3((*exp)->var, "\'", 0);
					free((*exp)->cmds[i]);
					(*exp)->cmds[i] = (*exp)->var;
				}
				free(trim);
			}
		}
	}
	return ;
}

void	exp_line(t_exp **exp)
{
	int		i;
	char	*trim;

	i = -1;
	while ((*exp)->cmds[++i])
	{
		if (strchr((*exp)->cmds[i], '$'))
		{
			trim = ft_strtrim((*exp)->cmds[i], "$\"");
			if (getenv(trim))
			{
				(*exp)->var = ft_strdup(getenv(trim));
				free((*exp)->cmds[i]);
				(*exp)->cmds[i] = (*exp)->var;
			}
			free(trim);
		}
		else
		{
			trim = ft_strtrim((*exp)->cmds[i], "\"");
			free((*exp)->cmds[i]);
			(*exp)->cmds[i] = ft_strdup(trim);
			free(trim);
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
	char	*tmp;

	tmp = NULL;
	exp = ft_calloc(sizeof(t_exp), 1);
	line = exit_exp(line);
	if (strchr(line, '$') && !strchr(line, ' '))
	{
		exp->trim = ft_strtrim(line, "$\"");
		if (getenv(exp->trim))
		{
			free(line);
			line = ft_strdup(getenv(exp->trim));
		}
		else if (strchr(line, '\"') && strchr(line, '$') && strchr(line, '\''))
		{
			apex_exp(&exp, line);
			free(line);
			line = exp->cmds[0];
			free(exp->cmds);
		}
		free(exp->trim);
	}
	else if (strchr(line, '$') && strchr(line, ' '))
	{
		tmp = line;
		line = multi_exp(&exp, line);
	}
	free(tmp);
	free(exp);
	return (line);
}
