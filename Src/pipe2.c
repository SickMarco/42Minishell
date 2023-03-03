/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:19:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/03 16:29:00 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void	ft_perrex(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
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
			pipe(prev_pipe_fds);
			pid = fork();///int
			if (pid == 0)//child
			{
				close(prev_pipe_fds[1]);
				dup2(prev_pipe_fds[0], STDIN_FILENO);
				close(prev_pipe_fds[0]);
				if (out_fd != STDOUT_FILENO)
				{
					dup2(out_fd, STDOUT_FILENO);
					close(out_fd);
				}
				execve(args[0], args, NULL);
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)//padre
			{
				close(prev_pipe_fds[0]);
				close(out_fd);
				out_fd = prev_pipe_fds[1];
				arg_count = 0;
			}
			else
				ft_perrex("fork");
			i++;
		}
		else if (!(ft_strncmp((char *)(lst->content), "<",
						ft_sl((char *)(lst->content)))))
		{
			char	*filename;

			lst = lst->next;
			filename = ft_strdup((char *)(lst->content));
			in_fd = open(filename, O_RDONLY);
			if (in_fd < 0)
				ft_perrex("open");
			free(filename);
			i = j;
		}
		else if (!(ft_strncmp((char *)(lst->content), ">", ft_sl((char *)(lst->content)))))
		{
			out_fd = open((char *)(lst->next->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (out_fd < 0)
				ft_perrex("open");
		}
		else if (!(ft_strncmp((char *)(lst->content), ">>", ft_sl((char *)(lst->content)))))
		{
			out_fd = open((char *)(lst->next->content), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (out_fd < 0)
				ft_perrex("open");
		}
		else
		{
			int j = i;
			while (command[j] != ' ' && command[j] != '|' && command[j] != '<' && command[j] != '>' && command[j] != '\0')
				j++;
			args[arg_count] = malloc(j - i + 1);
			memcpy(args[arg_count], &command[i], j - i);
			args[arg_count][j - i] = '\0';
			arg_count++;
			i = j;
		}
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
	execute_multi_pipe("ls | grep .c > output.txt | cat < output.txt");
	return 0;
}
