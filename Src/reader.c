/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:29:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/13 12:35:25 by mabaffo          ###   ########.fr       */
/*   Updated: 2023/03/05 19:29:13 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_endread(char *c, char **line, char **origin)
{
	int	a;

	if (!line || !(*line))
		return (1);
	if (*c == '\'' || *c == '\"')
	{
		if (ft_strchr(*line, *c))
		{
			a = 1;
			ft_search_last_n_scale(line, *c);
			ft_freejoin(origin, line);
		}
		else
			a = 0;
	}
	else if (!(ft_strncmp(c, *line, ft_sl(c)))
		&& (ft_sl(c) == (ft_sl(*line) - 1)))
	{
		a = 1;
		if (*line)
			free(*line);
	}
	else
		a = 0;
	return (a);
}

void	ft_reader(char **origin, char *prompt, char *c)
{
	char	*line;

	g_exit = 0;
	if (!ft_strncmp(c, "\'", ft_strlen(c)) || !ft_strncmp(c, "\"", ft_strlen(c)))
		ft_search_last_n_scale(origin, c[0]);
	while (g_exit != 130)
	{
		write(1, prompt, ft_strlen(prompt));
		line = gnl(0);
		if (line && *line)
		{
			if (ft_endread(c, &line, origin))
				break ;
			if (!ft_strncmp("heredoc> ", prompt, ft_sl(prompt)))
				ft_putinhdoc_n_free(&line);
			else
				ft_freejoin(origin, &line);
		}
		else
			break ;
	}
}

static void	ft_search_first(char **origin)
{
	int	i;

	i = 0;
	while (*origin[i])
	{
		if (*origin[i] == '\'')
		{
			ft_reader(origin, "quote> ", "\'");
			break ;
		}
		else if (*origin[i] == '\"')
		{
			ft_reader(origin, "dquote> ", "\"");
			break ;
		}
		i++;
	}
}

void	ft_readifyouneed(char **origin, t_data **ms)
{
	int		dc;
	int		sc;
	char	*sep;

	ft_count_quotes(*origin, &dc, &sc);
	if ((dc && dc % 2) || (sc && sc % 2))
		ft_addnl(origin);
	if (dc && dc % 2 != 0 && !(sc % 2))
		ft_reader(origin, "dquote> ", "\"");
	else if (sc && sc % 2 != 0 && !(dc % 2))
		ft_reader(origin, "quote> ", "\'");
	else if (dc && sc && (sc % 2) && (dc % 2))
		ft_search_first(origin);
	else if (ft_strnstr(*origin, "<<", ft_sl(*origin)) && !is_in_quotes(*origin, "<<"))
	{
		sc = ft_strnstr(*origin, "<<", ft_strlen(*origin)) - *origin;
		sep = ft_substr(*origin, sc + 2 + ft_splen(&(origin[0][sc + 2])),
				ft_lts(&(origin[0][sc + 2 + ft_splen(&(origin[0][sc + 2]))])));
		ft_heredoc(origin, sep, sc);
		(*ms)->hist = false;
	}
	else if (origin[0][ft_strlen(*origin) - 1] == '|')
		ft_promptpipe(origin);
}
/*
int main(void)
{
	char *s;
	s = malloc(6);
//	s[0] = 'c'; s[1] = 'a'; s[2] = '<'; 
//	s[3] = '<'; s[4] = 'f'; s[5] = 32; s[6] = '$'; s[7] = 0;
	s[0] = 'c'; s[1] = '\''; s[2] = 'c'; s[3] = 'g'; s[4] = 'f'; s[5] = 0;
	ft_readifyouneed(&(s));
	printf("\n\n%s\n", s);
}*/
