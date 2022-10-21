/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:29:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/21 22:36:34 by hkaddour         ###   ########.fr       */
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
	int		len_args;
	int		hrdoc_f;
	int		proc;
	int		fd[2];
	int		f_in;
	int		f_out;
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
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * loop over commands by sharing
 * pipes.
 */
static void
pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		pipe(fd);
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
			execvp((*cmd)[0], *cmd);
			exit(1);
		}
		else {
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int
main(int argc, char *argv[])
{
	char *ls[] = {"ls", "-al", NULL};
	char *rev[] = {"rev", NULL};
	char *nl[] = {"nl", NULL};
	char *cat[] = {"cat", "-e", NULL};
	char **cmd[] = {ls, rev, nl, cat, NULL};

	pipeline(cmd);
	return (0);
}
