/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:25:59 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/07 14:25:52 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
