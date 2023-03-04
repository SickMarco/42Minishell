/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:01:01 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/04 19:52:21 by mbozzi           ###   ########.fr       */
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

typedef struct s_exp {
	int			len;
	int			start;
	char		*var;
	int			var_len;
	char		*exp_var;
	char		*exp_cmd;
}				t_exp;

typedef struct s_data {
	char		*input;
	char		**env;
	char		*pwd;
	char		**path;
	char		*prompt;
	char		**cmd;
	t_exp		*exp;
	pid_t		pid;
	bool		hist;
}				t_data;

//			BUILTINS		//

void	ft_pwd(t_data **data);
void	ft_clear(void);
void	ft_cd(t_data **data);
void	ft_env(t_data **ms);
void	ft_export(t_data **data);
void	ft_unset(t_data **ms);
void	ft_echo(t_data **ms);

//			PARSING			//

void	ft_expander(t_data **ms);
bool	ft_builtin(t_data **data);
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
void	cmd_builder(t_data **ms);
void	signal_handler(t_data **ms);
void	ctrlc_handler(int sig);
void	executor(t_data **ms);
void	no_cmd(t_data **ms);
int		exit_exp(t_data **ms);
int		env_len(t_data **ms, int i);

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
void	heredoc_fork(t_data **ms, char *cmd);

#endif
