/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:01:01 by mbozzi            #+#    #+#             */
/*   Updated: 2023/02/14 19:42:30 by mbozzi           ###   ########.fr       */
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

typedef struct s_data {
	char		*user;
	char		*input;
	char		*pwd;
	char		*trimmed;
}				t_data;

//			BUILTINS		//

void	pwd(t_data **data);
void	history(t_data **data);

#endif