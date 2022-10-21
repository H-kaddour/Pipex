/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:51:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/21 15:34:08 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_heredoc_error(t_data *data)
{
	if (data->len_args == 5)
		return (0);
	perror("error in args of heredoc\n");
	return (1);
}

void	read_heredoc_input(t_data *data)
{
	char	*line;
	char	*hrdoc;
	int		len;

	hrdoc = ft_strdup("");
	while (21)
	{
		ft_putstr_fd("> ", 0);
		line = grab_line(0);
		if (!line)
			exit(0);
		len = ft_strlen(data->av[1]);
		if (ft_strlen(line) > ft_strlen(data->av[1]))
			len = ft_strlen(line);
		if (!ft_strncmp(line, data->av[1], len))
			break ;
		hrdoc = ft_strjoin(hrdoc, ft_strjoin(line, "\n"));
	}
	ft_putstr_fd(hrdoc, data->fd[1]);
	close(data->fd[1]);
	exit(0);
}

void	run_cmd_heredoc(t_data *data)
{
	int	pid;

	if (pipe(data->fd) < 0)
	{
		perror("Error in pipe\n");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error in fork\n");
		exit(1);
	}
	if (pid == 0)
	{
		close(data->fd[0]);
		dup2(data->hrdoc_f, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		execute(data->av[2], data);
	}
	if (pid > 0)
	{
		wait(0);
		close(data->fd[1]);
		close(data->hrdoc_f);
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->f_out, STDOUT_FILENO);
		close(data->fd[0]);
		execute(data->av[3], data);
	}
}

void	run_heredoc(t_data *data)
{
	int		pid;

	if (check_heredoc_error(data))
		return ;
	data->f_out = open(data->av[4], O_RDWR | O_CREAT | O_APPEND, 0664);
	if (data->f_out < 0)
		perror("file out fails to read :(\n");
	if (pipe(data->fd) < 0)
	{
		perror("Error in pipe\n");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error in fork\n");
		exit(1);
	}
	if (pid == 0)
	{
		close(data->fd[0]);
		read_heredoc_input(data);
	}
	if (pid > 1)
	{
		wait(0);
		close(data->fd[1]);
		data->hrdoc_f = data->fd[0];
		run_cmd_heredoc(data);
	}
}
