/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:29:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/22 15:41:19 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	char	*cmd;
	int		f_in;
	int		f_out;
	int		*tab_pipe;
	struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
	char	**av;
	char	**env;
	char	**path;
	char	**cmd_opt;
	int		len_args;
	int		hrdoc_f;
	int		proc;
	int		fd[2];
	int		f_in;
	int		f_out;
	t_cmd	*cmd;
}	t_data;

typedef struct grab_line
{
	char		*ptr;
	char		*tmp;
	char		*buff;
	char		*line;
}	t_gnl;

/******* Function mandatory **********/
void	processes_making(t_data *data);
void	get_path(t_data *data, char **env);

/******* Function bonus **********/
void	pipeline(t_data *data);
void	get_path(t_data *data, char **env);
void	execute(char *cmd, t_data *data);
void	run_heredoc(t_data *data);
char	*grab_line(int fd);

#endif
