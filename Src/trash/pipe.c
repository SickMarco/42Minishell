/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:19:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/03 15:26:49 by mabaffo          ###   ########.fr       */
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

void execute_multi_pipe(char* command)
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
	while (command[i] != '\0')
	{
		while (command[i] == ' ')
			i++;
		if (command[i] == '|')
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
		else if (command[i] == '<')
		{
			i++;
			while (command[i] == ' ')
				i++;
			int j = i;
			while (command[j] != ' ' && command[j] != '|' && command[j] != '<' && command[j] != '>' && command[j] != '\0')
				j++;
			char* filename = malloc(j - i + 1);
			memcpy(filename, &command[i], j - i);
			filename[j - i] = '\0';
			in_fd = open(filename, O_RDONLY);
			if (in_fd < 0)
				ft_perrex("open");
			free(filename);
			i = j;
		}
		else if (command[i] == '>')
		{
			i++;
			if (command[i] == '>')
			{
				i++;
				out_fd = open(&command[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
            }
			else
				out_fd = open(&command[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (out_fd < 0)
				ft_perrex("open");
			while (command[i] != ' ' && command[i] != '|' && command[i] != '<' && command[i] != '>' && command[i] != '\0')
				i++;
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
