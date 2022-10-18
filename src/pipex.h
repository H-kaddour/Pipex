/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:29:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/18 18:08:49 by hkaddour         ###   ########.fr       */
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

typedef struct s_data
{
	char	**av;
	char	**env;
	char	**path;
	char	**cmd_opt;
	char	**leak;
	int		i;
	int		proc;
	int		fd[2];
	int		f_in;
	int		f_out;
}	t_data;

void	processes_making(t_data *data);
void	get_path(t_data *data, char **env);
char *add_join(t_data *data, char *path, char *cmd);
void	free_all(t_data *data);

#endif
