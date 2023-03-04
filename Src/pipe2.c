/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:19:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/04 15:21:33 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "../minishell.h"

typedef struct s_cmd
{
	char	**arg;
	int		pipe_fds[2];
	int		prev_pipe_fds[2];

}	t_cmd;

void	ft_perrex(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	ft_cmdlen(t_list *lst)
{
	char	*str;
	int		i;

	i = 0;
	if (lst)
		str = (char *)(lst->content);
	while (lst && !(ft_strncmp(str, "|", ft_sl(str) ||
		ft_strncmp(str, "<", ft_sl(str)) ||
		ft_strncmp(str, ">", ft_sl(str)) ||
		ft_strncmp(str, ">>", ft_sl(str)))))
	{
		i++;
		lst = lst->next;
		if (lst)
			str = (char *)(lst->content);
	}
	return (i);
}

void	ft_fillarg(t_cmd *cmd, t_list **lst)
{
	int	len;
	int	i;

	i = 0;
	len = ft_cmdlen(*lst);
	cmd->arg = malloc(len + 1);
	if (!(cmd->arg))
		return ;
	(cmd->arg)[len] = NULL;
	while (i < len)
	{
		(cmd->arg)[i] = (char *)((*lst)->content);
		i++;
	}
}

void	ft_freearg(t_cmd *cmd)
{
	char	**arg;
	int		i;

	arg = cmd->arg;
	if (!arg)
		return ;
	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void execute_multi_pipe(t_list *lst)
{
	char	*args[1024];
	int		arg_count;
	int		pipe_fds[2];
	int		prev_pipe_fds[2];
	int		in_fd = STDIN_FILENO;
	int		out_fd = STDOUT_FILENO;
	int		i;
	int		pid;

	arg_count = 0;
	i = 0;
	while (lst->content)
	{
		if (!(ft_strncmp((char *)(lst->content), "|",
					ft_sl((char *)(lst->content)))))
		{
			
		}
		else if (!(ft_strncmp((char *)(lst->content), "<",
						ft_sl((char *)(lst->content)))))
		{
			
		}
		else if (!(ft_strncmp((char *)(lst->content), ">", ft_sl((char *)(lst->content)))))
		{
			
		}
		else if (!(ft_strncmp((char *)(lst->content), ">>", ft_sl((char *)(lst->content)))))
		{
			
		}
		else
			ft_fillarg(&cmd, &lst);
	}
	args[arg_count] = NULL;
	pid = fork();///int
	if (pid == 0)//child
	{
		dup2(in_fd, STDIN_FILENO);
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO);
		execve(args[0], args, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)//padre
	{
		waitpid(pid, NULL, 0);
		close(in_fd);
		close(out_fd);
		for (int j = 0; j < arg_count; j++)
			free(args[j]);
	}
	else
		ft_perrex("fork");
}

int main()
{
	char *s = ft_strdup("ls | grep .c > output.txt | cat < output.txt");
	execute_multi_pipe(ft_subsplit((ft_split1(s))));
	return 0;
}
