/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:21:19 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/04 19:03:30 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putinhdoc_n_free(char **line)
{
	int	fd;

	fd = open(HERED, O_RDWR | O_CREAT | O_APPEND, 0666);
	write(fd, *line, ft_sl(*line));
	close(fd);
	if (*line && **line)
		free(*line);
}

void	ft_heredoc(char **origin, char *sep, int till_sep)
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

void	ft_freejoin(char **origin, char **line)
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

void	ft_promptpipe(char **origin)
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
