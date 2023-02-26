#include "../minishell.h"

void	ft_count_quotes(char *s, int *dc, int *sc)
{
	*dc = 0;
	*sc = 0;
	if (!s || !(*s))
		return (NULL);
	while (*s)
	{
		if (*s == '\'')
			(*sc)++;
		else if (*s == '\"')
			(*dc)++;
		s++;
	}
}

void	ft_reader(char **origin, char *prompt, char *c)
{
	char *line;
	char *tmp;

	while (1)
	{
		printf(prompt);
		line = get_next_line(0);
		if (line && *line)
		{
			if (!ft_strncmp(c, line, ft_strlen(c)))
			{
				free(line);
				break ;
			}
			tmp = *origin;
			*origin = ft_strjoin(*origin, line);
			free(tmp);
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

void	ft_readifyouneed(char **origin)
{
	int		dc;
	int		sc;
	char	*hds;

	ft_count_quotes(*origin, *dc, *sc);
	if (dc && dc % 2 != 0 && !(sc % 2))
		ft_reader(origin, "dquote> ", "\"");
	else if (sc && sc % 2 != 0 && !(dc % 2))
		ft_reader(origin, "quote> ", "\'");
	else if (dc && sc && (sc % 2) && (dc % 2))
		ft_search_first(origin);
	else if (ft_strnstr(*origin, "<<", ft_strlen(*origin)))
	{
		hds = ft_strdup((ft_strnstr(*origin, "<<", ft_strlen(*origin))) + 2);
		ft_reader(origin, "heredoc> ", hds);
		free(hds);
	}
}
