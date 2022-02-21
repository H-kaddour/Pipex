/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:03:00 by hkaddour          #+#    #+#             */
/*   Updated: 2022/02/21 18:23:34 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_exec(char *av, char **env)
{
	t_end	pipex;
	int		i;

	i = 0;
	pipex.o_path = ft_get_path(env);
	pipex.flags = ft_split(av, ' ');
	i = 0;
	while (pipex.o_path[i] != NULL)
	{
		pipex.n_path = ft_strjoin(pipex.o_path[i], pipex.flags[0]);
		if (access(pipex.n_path, F_OK) != -1)
		{
			execve(pipex.n_path, pipex.flags, env);
			break ;
		}
		i++;
	}
	perror("Invalid command!\n");
	exit(1);
}

void	ft_pipex_it(int filein, int fileout, char **av, char *env[])
{
	t_end	pix;

	pipe(pix.fd);
	pix.child = fork();
	if (pix.child == -1)
	{
		perror("fork fails :(\n");
		exit(1);
	}
	if (pix.child == 0)
	{
		close(pix.fd[0]);
		dup2(filein, STDIN_FILENO);
		dup2(pix.fd[1], STDOUT_FILENO);
		ft_exec(av[2], env);
	}
	if (pix.child > 0)
	{
		wait(0);
		close(pix.fd[1]);
		dup2(pix.fd[0], STDIN_FILENO);
		dup2(fileout, STDOUT_FILENO);
		ft_exec(av[3], env);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_end	files;

	if (ac == 5)
	{
		files.fdin = open(av[1], O_RDONLY);
		if (files.fdin < 0)
			perror("file in fails to read :(");
		files.fdout = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (files.fdout == -1)
			perror("file out fails to creat :(");
		ft_pipex_it(files.fdin, files.fdout, av, envp);
	}
	else
		perror("Check your argument!\n");
}
