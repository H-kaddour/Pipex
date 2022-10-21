/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:25:59 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/19 09:23:18 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	execute(char *cmd, t_data *data)
{
	int		i;
	char	*pth_cmd;
	char	*hold;

	i = 0;
	get_path(data, data->env);
	data->cmd_opt = ft_split(cmd, ' ');
	while (data->path[i])
	{
		hold = ft_strjoin("/", data->cmd_opt[0]);
		pth_cmd = ft_strjoin(data->path[i], hold);
		if (!access(pth_cmd, F_OK))
		{
			if (!access(pth_cmd, X_OK))
				execve(pth_cmd, data->cmd_opt, data->env);
			else
				perror("Permission denied :/\n");
		}
		free(hold);
		free(pth_cmd);
		i++;
	}
	perror("Invalid command! :/\n");
	exit(1);
}

void	processes_making(t_data *data)
{
	if (pipe(data->fd) < 0)
		exit (2);
	data->proc = fork();
	if (data->proc < 0)
	{
		perror("fork fails :(\n");
		exit(2);
	}
	if (data->proc == 0)
	{
		close(data->fd[0]);
		dup2(data->f_in, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		execute(data->av[1], data);
	}
	if (data->proc > 0)
	{
		wait(0);
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->f_out, STDOUT_FILENO);
		execute(data->av[2], data);
	}
}
