/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:00:01 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/13 21:00:08 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_elem(char *s, char c)
{
	int i;
	int count;

	if (!s || !(*s) || !c)
		return (0);
	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == c)
			count++;
	}
	return (count);
}

static int is_in_quote(char *before, char *after, char quote)
{
	int n1;
	int n2;

	n1 = count_elem(before, quote);
	n2 = count_elem(after, quote);
	if (n1 && n2 && n1 % 2 && n2 % 2)
		return (1);
	else
		return (0);
}

int	is_in_quotes(char *origin, char *ob)
{
	char	*str_before;
	char	*str_after;
	char	*ob_posix;
	int		ret;

	ret = 0;
	ob_posix = ft_strnstr(origin, "<<", ft_sl(origin));
	str_before = ft_substr(origin, 0, ob_posix - origin);
	str_after = ft_strdup(ob_posix + ft_sl(ob));
	if (is_in_quote(str_before, str_after, '\"')
		    || is_in_quote(str_before, str_after, '\''))
		ret++;
	free(str_before);
	if (str_after && *str_after)
		free(str_after);
	return (ret);
}
