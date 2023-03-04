/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:41:52 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/04 16:31:19 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int piper()
{//This code block is handling the case when a pipe | is encountered in the command.

			pipe(prev_pipe_fds);
			pid = fork();///int
						/*	It creates a new pipe using pipe()
							and forks a child process using fork() */

			if (pid == 0)//child
			{
				/* In the child process, the read end of the previous pipe is closed
				 * and its file descriptor is duplicated onto
				 * the standard input file descriptor (STDIN_FILENO) using dup2().*/
				close(prev_pipe_fds[1]);
				dup2(prev_pipe_fds[0], STDIN_FILENO);
				close(prev_pipe_fds[0]);
				/* If the current output file descriptor is not equal to standard output (STDOUT_FILENO),
				 * its file descriptor is duplicated onto the standard output file descriptor using dup2(). */
				if (out_fd != STDOUT_FILENO)
				{
					dup2(out_fd, STDOUT_FILENO);
					close(out_fd);
				}
				execve(args[0], args, NULL);//Then execve() is called to execute the current command.
				exit(EXIT_FAILURE);
			}

			else if (pid > 0)//padre
			{
				/*
				 * In the parent process, the write end of the previous pipe is closed,
				 * the current output file descriptor is closed,
				 * and its file descriptor is set to the write end of the current pipe. */
				close(prev_pipe_fds[0]);
				close(out_fd);
				out_fd = prev_pipe_fds[1];

				arg_count = 0;//The argument count is set to 0 to prepare for the next command.
			}
			else//If fork() fails, ft_perrex() is called to exit the program with an error message.
				ft_perrex("fork");
			i++;
}
/*
int inputr()//<
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

int outputr()//>
{
out_fd = open((char *)(lst->next->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (out_fd < 0)
				ft_perrex("open");

}

int appendr()//>>
{
out_fd = open((char *)(lst->next->content), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (out_fd < 0)
				ft_perrex("open");
}*/
