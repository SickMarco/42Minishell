#include "../minishell.h"

void	ft_search_last_n_scale(char **origin, char c);

void	ft_count_quotes(char *s, int *dc, int *sc)
{
	*dc = 0;
	*sc = 0;
	if (!s || !(*s))
		return ;
	while (*s)
	{
		if (*s == '\'')
			(*sc)++;
		else if (*s == '\"')
			(*dc)++;
		s++;
	}
}

void	ft_promptpipe(char **origin)
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

void	ft_reader(char **origin, char *prompt, char *c)
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
			if (!ft_strncmp(c, line, ft_strlen(c)))
			{
				free(line);
//				printf("orig = %s\n", *origin);
				break ;
			}
			tmp = *origin;
			*origin = ft_strjoin(*origin, line);
			//printf("\n%s\n", *origin);
			free(tmp);
			free(line);
		}
		else
			break ;
	}
}

void	ft_search_first(char **origin)
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

void	ft_search_last_n_scale(char **origin, char c)
{
	int		lstx;
	int		i;
	char	*tmp;

	lstx = -1;
	i = 0;
	while (origin[0][i])
	{
		if (origin[0][i] == c)
			lstx = i;
		i++;
	}
	if (lstx > -1)
	{
		i = lstx;
		while (origin[0][i])
		{
			origin[0][i] = origin[0][i + 1];
			i++;
		}
		tmp = ft_strdup(*origin);
		free(*origin);
		*origin = tmp;
	}
}

char	*ft_sp(char *s)
{
	int	i;

	if (!s | !(*s))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != 32)
		i++;
	while (s[i] == 32)
		i++;
	if (s[i])
		return (&s[i]);
	return (NULL);
}

int	ft_lts(char *s)
{
	int	i;

	if (!s || !(*s))
		return (0);
	i = 0;
	while (s[i] && s[i] != 32)
		i++;
	return (i);
}

void ft_heredoc(char **origin, char *sep, int till_sep)
{/*
	printf("sep = %s\n", sep);
	printf("\ntill_sep = %d\n", till_sep);*/
	char *start;
	char *end;

	start = ft_substr(*origin, 0, till_sep);
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
		sep = ft_substr(*origin, sc + 2, ft_lts(&(origin[0][sc + 2])));
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
