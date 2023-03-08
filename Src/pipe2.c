/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:22:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/03/08 14:11:51 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "../minishell.h"

char **env;

typedef struct s_cmd
{
	char	**arg;
	char	*cmd_path;
	int		pipe_fds[2];
	int		prev_pipe_fds[2];
	int		in_fd;
	int		out_fd;
}	t_cmd;

void	ft_perrex(char *s);
void	ft_freelist(t_list **lst);
int		ft_cmdlen(t_list *lst);
void	ft_fillarg(t_cmd *cmd, t_list **lst);
void	ft_freearg(t_cmd *cmd);
char	**path_init(void);
char	*path_search(char **path, char *cmd);

void execute_multi_pipe(t_list *lst)
{
//	char	*args[1024];
//	int		arg_count;
	t_list	*head;
	int		pid;
	t_cmd	cmd;
	char	**path;

	path = path_init();
	head = lst;
	cmd.in_fd = STDIN_FILENO;
	cmd.out_fd = STDOUT_FILENO;
	while (lst)
	{
		if (!(ft_strncmp((char *)(lst->content), "|",
					ft_sl((char *)(lst->content)))))
		{
			lst = lst->next;
			if (!lst)
				break ;
			pipe(cmd.prev_pipe_fds);
			pid = fork();///int
			/*	It creates a new pipe using pipe()
			 *	and forks a child process using fork() */
			if (pid == 0)//child
			{
/*				close(cmd.pipe_fds[0]);//gpt
				dup2(cmd.pipe_fds[1], STDOUT_FILENO);
				close(cmd.pipe_fds[1]);
*/
//				pipe(cmd.prev_pipe_fds);
//
				dup2(cmd.prev_pipe_fds[1], 1);
				close(cmd.prev_pipe_fds[1]);
				/* In the child process, the read end of the previous pipe is closed
				 * and its file descriptor is duplicated onto
				 * the standard input file descriptor (STDIN_FILENO) using dup2().*/
/*				close(cmd.prev_pipe_fds[1]);
				dup2(cmd.prev_pipe_fds[0], STDIN_FILENO);
				close(cmd.prev_pipe_fds[0]);
*/
				/* If the current output file descriptor is not equal to standard output (STDOUT_FILENO),
				* its file descriptor is duplicated onto the standard output file descriptor using dup2().*/
				if (cmd.out_fd != STDOUT_FILENO)
				{
					dup2(cmd.out_fd, STDOUT_FILENO);
					close(cmd.out_fd);
				}
				cmd.cmd_path = path_search(path, cmd.arg[0]);
				execve(cmd.cmd_path, cmd.arg, env);//Then execve() is called to execute the current command.
				free(cmd.cmd_path);
				exit(EXIT_FAILURE);
			}

			else if (pid > 0)//padre
			{
			/*
			 * In the parent process, the write end of the previous pipe is closed,
			 * the current output file descriptor is closed,
			 * and its file descriptor is set to the write end of the current pipe. */
				close(cmd.prev_pipe_fds[0]);
				close(cmd.out_fd);
				waitpid(pid, NULL, 0); 
				cmd.out_fd = cmd.prev_pipe_fds[1];
				close(cmd.prev_pipe_fds[1]);///
				ft_freearg(&cmd);///
//				arg_count = 0;//The argument count is set to 0 to prepare for the next command.
			}
			else//If fork() fails, ft_perrex() is called to exit the program with an error message.
				ft_perrex("fork");
//			lst = lst->next;//i++;
		}
		else if (!(ft_strncmp((char *)(lst->content), "<",
						ft_sl((char *)(lst->content)))))
		{
			lst = lst->next;
			if (!lst)
				break ;
			cmd.in_fd = open((char *)(lst->content), O_RDONLY);
			if (cmd.in_fd < 0)
				ft_perrex("open");
			free(lst->content);
			lst = lst->next;
		}
		else if (!(ft_strncmp((char *)(lst->content), ">",
						ft_sl((char *)(lst->content)))))
		{
			lst = lst->next;
			if (!lst)
				break ;
			cmd.out_fd = open((char *)(lst->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (cmd.out_fd < 0)
				ft_perrex("open");
			lst = lst->next;
		}
		else if (!(ft_strncmp((char *)(lst->content), ">>",
						ft_sl((char *)(lst->content)))))
		{
			lst = lst->next;
			if (!lst)
				break ;
			cmd.out_fd = open((char *)(lst->content), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (cmd.out_fd < 0)
				ft_perrex("open");
			lst = lst->next;
		}
		else
		{
	//		printf("F fillarg\n");
			ft_fillarg(&cmd, &lst);
	//		printf("%s\n", cmd.arg[0]);
		}
	}
//	args[arg_count] = NULL;
	pid = fork();///int
	if (pid == 0)//child
	{
	//	printf("F !\n");
		dup2(cmd.in_fd, STDIN_FILENO);
		if (cmd.out_fd != STDOUT_FILENO)
			dup2(cmd.out_fd, STDOUT_FILENO);
//		printf("%s\n", cmd.arg[0]);
		cmd.cmd_path = path_search(path, cmd.arg[0]);
		execve(cmd.cmd_path, cmd.arg, env);
		free(cmd.cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)//padre
	{
	//	printf("F ?"); 
		waitpid(pid, NULL, 0);
		close(cmd.in_fd);
		close(cmd.out_fd);
		
	}
	else
		ft_perrex("fork");
	ft_freelist(&head);
}



int main(int ac, char **av, char **envp)
{
	(void)(ac);
	(void)(av);
	env = envp;
	char *s = ft_strdup("ls -a | pwd");// | grep .c > output.txt | cat < output.txt");
	t_list *lst = ft_subsplit((ft_split1(s)));
//	ft_print_slst(lst);
	execute_multi_pipe(lst);
	return 0;
}

void	ft_perrex(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	ft_freelist(t_list **lst)
{
	t_list	*nxt;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		nxt = (*lst)->next;
		if ((*lst)->content)
			free((*lst)->content);
		free((*lst));
		*lst = nxt;
	}
}

int	ft_cmdlen(t_list *lst)
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
	printf("cmdlen %d\n", i);
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
		(*lst) = (*lst)->next;
	}
}

void	ft_freearg(t_cmd *cmd)
{
	char	**arg;
//	int		i;

	arg = cmd->arg;
	if (!arg)
		return ;
/*	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}*/
	free(arg);
}

char	**path_init(void)
{
	char	**path;
	int		i;

	i = -1;
	path = ft_split(getenv("PATH"), ':');
	while (path[++i])
		path[i] = ft_strjoin2(path[i], "/");

	return (path);
}

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
