/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:01:01 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/11 19:06:03 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Src/MyLib/mylib.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/resource.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/ioctl.h>

# ifndef HERED
#  define HERED "Src/.obj/.heredoc"
# endif

extern int	g_exit;

typedef struct s_cmd
{
	char			**cmds;
	char			*cmd;
	int				in_fd;//for redirects, -1 mean no redirects
	int				out_fd;//idem
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_exp {
	char	**cmds;
	char	*var;
	char	*ret;
	char	*trim;
}				t_exp;

typedef struct s_data {
	char		*input;
	char		**env;
	char		*pwd;
	char		**path;
	char		*prompt;
	char		**cmd;
	pid_t		pid;
	bool		hist;
	int			fd;
	int			stdin_fd;
	int			stdout_fd;
	int			pipe;
	t_cmd		*cmd_list;
	t_list		*list;
}				t_data;

//			BUILTINS		//

bool	ft_builtin(t_data **data, t_cmd	*cmd);
bool	check_builtin(t_cmd *cmd);
void	ft_pwd(t_data **data);
void	ft_clear(void);
void	ft_cd(t_data **ms, t_cmd *cmd);
void	ft_env(t_data **ms);
void	ft_export(t_data **ms, t_cmd *cmd);
void	ft_unset(t_data **ms, t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	no_cmd(t_cmd *cmd);

//			PARSING			//

char	*ft_expander(char *line);
int		ft_countwords1(char *s);
void	ft_skip_space(char *s, int *i);
void	ft_close_quote(char *s, int *i, char c);
char	**ft_split1(char *s);
t_list	*ft_createlist(char **tab);
t_list	*ft_subsplit(char **tab);
int		ft_ischarofset(char c, char *set);
void	ft_trimone(char **args);
int		ft_sl(const char *s);

//			UTILS			//

void	ft_history(t_data **data);
void	free_for_all(t_data **ms);
int		ft_print_slst(t_list *lst);//for debugging
void	set_env(t_data **ms, char **envp);
void	ctrlc_handler(int sig);
char	*exit_exp(char *line);
int		env_len(t_data **ms, int i);
void	free_cmd(t_cmd *cmd);
void	ft_freelist(t_list **lst);
void	free_for_all2(t_data **ms);

//			EXECUTOR		//

void	cmd_builder(t_data **ms);
void	cmd_builder(t_data **ms);
void	signal_handler(t_data **ms);
void	ctrlc_handler(int sig);
void	executor(t_data **ms, t_cmd *cmd);
void	exec_cmd(t_data **ms, t_cmd *cmd_list);
void	executor(t_data **ms, t_cmd *cmd);
void	prnt_ctrl(int sig);
void	open_redir(t_cmd *cmd);
void	close_redir(t_data **ms, t_cmd *cmd);

//		PROMPT_READER		//

void	ft_readifyouneed(char **origin, t_data **ms);
void	ft_count_quotes(char *s, int *dc, int *sc);
void	ft_search_last_n_scale(char **origin, char c);
char	*ft_sp(char *s);
int		ft_lts(char *s);
int		ft_splen(char *s);
char	*gnl(int fd);
void	ft_putinhdoc_n_free(char **line);
void	ft_heredoc(char **origin, char *sep, int till_sep);
void	ft_freejoin(char **origin, char **line);
void	ft_addnl(char **origin);
void	ft_promptpipe(char **origin);
void	ft_reader(char **origin, char *prompt, char *c);

//		CMD_LIST		//

void	ft_perrex(char *s);
t_cmd	*ft_cmdnew(t_list **lst, char **path);
void	ft_cmd_addback(t_cmd **cmd, t_cmd *new);
t_cmd	*ft_cmdlast(t_cmd *cmd);
char	*path_search(char **path, char *cmd);
t_cmd	*create_cmdlst(t_list *lst, t_data *ms);
void	lst_freecont_n_skip(t_list **lst);
int		content_is(t_list *lst, const char *s);

#endif
