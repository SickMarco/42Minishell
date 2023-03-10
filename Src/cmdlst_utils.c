/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:50:12 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/10 15:02:33 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_search(char **path, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (path[++i] && ft_strncmp(cmd, ".", 1))
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	if (cmd)
	{
		while (cmd->next)
			cmd = cmd->next;
	}
	return (cmd);
}

void	ft_cmd_addback(t_cmd **cmd, t_cmd *new)
{
	if (cmd)
	{
		if (*cmd)
			ft_cmdlast(*cmd)->next = new;
		else
			*cmd = new;
	}
}

static int	ft_cmdslen(t_list *lst)
{
	char	*str;
	int		i;

	i = 0;
	if (lst)
		str = (char *)(lst->content);
	while (lst && ft_strncmp(str, "|", ft_sl(str)) &&
		ft_strncmp(str, "<", ft_sl(str)) &&
		ft_strncmp(str, ">", ft_sl(str)) &&
		ft_strncmp(str, ">>", ft_sl(str)))
	{
		i++;
		lst = lst->next;
		if (lst)
			str = (char *)(lst->content);
	}
	return (i);
}

t_cmd	*ft_cmdnew(t_list **lst, char **path)
{
	t_cmd	*cmdn;
	int		len;
	int		i;

	cmdn = malloc(sizeof(t_cmd));
	if (!cmdn)
		return (NULL);
	len = ft_cmdslen(*lst);
	cmdn->cmds = malloc(sizeof(char *) * (len + 1));
	if (!(cmdn->cmds))
		return (NULL);
	(cmdn->cmds)[len] = NULL;
	i = -1;
	while (++i < len)
	{
		(cmdn->cmds)[i] = (char *)((*lst)->content);
		*lst = (*lst)->next;
	}
	cmdn->cmd = path_search(path, (cmdn->cmds)[0]);
	cmdn->in_fd = -1;
	cmdn->out_fd = -1;
	cmdn->next = NULL;
	return (cmdn);
}
