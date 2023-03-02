/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:29:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/02 23:24:33 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_freejoin(char **origin, char **line)
{
	char	*tmp;

	if (!(*origin) || !(*line) || !line || !origin)
		return ;
	tmp = *origin;
	*origin = ft_strjoin(*origin, *line);
	if (tmp)
		free(tmp);
	if (*line)
		free(*line);
}

static void	ft_promptpipe(char **origin)
{
	char	*line;
	char	*tmp;

	g_exit = 0;
	write(1, "pipe> ", 6);
	line = gnl(0);
	if (line && *line)
	{
		tmp = *origin;
		*origin = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
}

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
			a = 0;;
	}
	else if (!(ft_strncmp(c, *line, ft_strlen(c))) && (ft_strlen(c) == (ft_strlen(*line) - 1)))
	{
		a = 1;
		if (*line)
			free(*line);
	}
	else
		a = 0;
	return (a);
}

static void	ft_reader(char **origin, char *prompt, char *c)
{
	char	*line;

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

static void ft_heredoc(char **origin, char *sep, int till_sep)
{
	char *start;
	char *end;

	if (!sep || !(*sep))
		return (void)(printf("heredoc: wrog syntax\n"));
	start = ft_substr(*origin, 0, till_sep);
	end = ft_sp(*origin + till_sep + 2 + ft_strlen(sep));
	if (end)
		end = ft_strdup(ft_sp(*origin + till_sep + 2 + ft_strlen(sep)));
	ft_reader(&start, "heredoc> ", sep);
	free(*origin);
	if (end)
	{
		*origin = ft_strjoin(start, end);
		free(end);
		free(start);
	}
	else
		*origin = start;
	free(sep);
}

void	ft_addnl(char **origin)
{
	char	*tmp;
	char	*nl;

	nl = malloc(2);
	if (!nl)
		return ;
	nl[0] = '\n';
	nl[1] = '\0';
	tmp = *origin;
	*origin = ft_strjoin(*origin, nl);
	free(tmp);
	free(nl);
}

void	ft_readifyouneed(char **origin)
{
	int		dc;
	int		sc;
	char	*sep;

	g_exit = 0;
	ft_count_quotes(*origin, &dc, &sc);
	if ((dc && dc % 2 ) || (sc && sc % 2))
		ft_addnl(origin);
	if (dc && dc % 2 != 0 && !(sc % 2))
		ft_reader(origin, "dquote> ", "\"");
	else if (sc && sc % 2 != 0 && !(dc % 2))
		ft_reader(origin, "quote> ", "\'");
	else if (dc && sc && (sc % 2) && (dc % 2))
		ft_search_first(origin);
	else if (ft_strnstr(*origin, "<<", ft_strlen(*origin)))
	{
		sc = ft_strnstr(*origin, "<<", ft_strlen(*origin)) - *origin;
		sep = ft_substr(*origin, sc + 2 + ft_splen(&(origin[0][sc + 2])),
				ft_lts(&(origin[0][sc + 2 + ft_splen(&(origin[0][sc + 2]))])));
		ft_heredoc(origin, sep, sc);
	}
	else if (origin[0][ft_strlen(*origin) - 1] == '|')
		ft_promptpipe(origin);
}
/*
int main(void)
{
	char *s;
	s = malloc(6);
//	s[0] = 'c'; s[1] = 'a'; s[2] = '<'; s[3] = '<'; s[4] = 'f'; s[5] = 32; s[6] = '$'; s[7] = 0;
	s[0] = 'c'; s[1] = '\''; s[2] = 'c'; s[3] = 'g'; s[4] = 'f'; s[5] = 0;
	ft_readifyouneed(&(s));
	printf("\n\n%s\n", s);
}*/
