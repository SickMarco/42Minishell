/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:01:01 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/22 17:40:37 by mbozzi           ###   ########.fr       */
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

typedef struct s_exp {
	int			len;
	int			start;
	char		*var;
	int			var_len;
	char		*exp_var;
	char		*exp_cmd;
}				t_exp;

typedef struct s_data {
	char		*user;
	char		*input;
	char		**env;
	char		*pwd;
	char		*home;
	char		*user_dir;
	char		**cmd;
	t_exp		*exp;
}				t_data;

//			BUILTINS		//

void	ft_pwd(t_data **data);
void	ft_history(t_data **data);
void	ft_clear(void);
void	ft_cd(t_data **data);
void	ft_env(t_data **ms);
void	ft_export(t_data **data);
void	user_dir_set(t_data **ms);
void	ft_unset(t_data **ms);
void	ft_echo(t_data **ms);

void	ft_expander(t_data **ms);
int		check_input(t_data **ms);
void	ft_parser(t_data **data);
int		ft_countwords1(char *s);
void	ft_skip_space(char *s, int *i);
void	ft_close_quote(char *s, int *i, char c);
char	**ft_split1(char *s);
t_list	*ft_createlist(char **tab);
t_list	*ft_subsplit(char **tab);
void	cmd_builder(t_data **ms);
void	free_for_all(t_data **ms);
int		ft_print_slst(t_list *lst);//for debugging
void	mat_dup(t_data **ms, char **envp);

#endif
