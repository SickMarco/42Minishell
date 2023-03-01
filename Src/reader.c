/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:29:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/01 17:50:33 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_promptpipe(char **origin)
{
	char	*line;
	char	*tmp;

	write(1, "pipe> ", 6);
	line = get_next_line(0);
	if (line && *line)
	{
		tmp = *origin;
		*origin = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
}

static void	ft_reader(char **origin, char *prompt, char *c)
{
	char	*line;
	char	*tmp;
	if (ft_strncmp(c, "\'", ft_strlen(c)) || ft_strncmp(c, "\"", ft_strlen(c)))
		ft_search_last_n_scale(origin, c[0]);
	while (1)
	{
		write(1, prompt, ft_strlen(prompt));
		line = get_next_line(0);
		if (line && *line)
		{
			if (!(ft_strncmp(c, line, ft_strlen(c))) && 
					(ft_strlen(c) == (ft_strlen(line) - 1)))
			{
				free(line);
				break ;
			}
			tmp = *origin;
			*origin = ft_strjoin(*origin, line);
			free(tmp);
			free(line);
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

void	ft_readifyouneed(char **origin)
{
	int		dc;
	int		sc;
	char	*sep;

	ft_count_quotes(*origin, &dc, &sc);
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
