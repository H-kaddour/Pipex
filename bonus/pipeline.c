/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:34:23 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/07 15:29:46 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	creates_pipe(t_data *data)
{
	t_cmd	*trav;

	add_cmd(data);
	trav = data->cmd;
	while (trav->next)
	{
		if (pipe(data->fd) < 0)
		{
			perror("Resource temporarily unavailable\n");
			exit(2);
		}
		trav->tab_pipe = malloc(sizeof(int) * 2);
		trav->tab_pipe[0] = data->fd[1];
		trav->tab_pipe[1] = data->fd[0];
		trav->f_out = data->fd[1];
		trav = trav->next;
		trav->f_in = data->fd[0];
	}
	trav->tab_pipe = malloc(sizeof(int) * 2);
	trav->tab_pipe[0] = data->fd[1];
	trav->tab_pipe[1] = data->fd[0];
}

static void	open_files(t_data *data)
{
	data->f_in = open(data->av[0], O_RDONLY);
	if (data->f_in < 0)
	{
		perror("file in fails to open :(\n");
		exit(2);
	}
	data->f_out = open(data->av[data->len_args - 1], \
			O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (data->f_out < 0)
	{
		perror("file out fails to open :(\n");
		exit(2);
	}
	creates_pipe(data);
}

static void	child_process(t_data *data, t_cmd *trav)
{
	dup2(trav->f_in, STDIN_FILENO);
	dup2(trav->f_out, STDOUT_FILENO);
	close(trav->tab_pipe[0]);
	close(trav->tab_pipe[1]);
	execute(trav->cmd, data);
}

static void	parent(void)
{
	while (21)
	{
		if (waitpid(-1, 0, 0) == -1)
			break ;
	}
}

void	pipeline(t_data *data)
{
	t_cmd	*trav;
	t_cmd	*p_trav;

	open_files(data);
	trav = data->cmd;
	p_trav = 0;
	while (trav)
	{
		data->proc = fork();
		if (data->proc < 0)
		{
			perror("Error in fork\n");
			exit(2);
		}
		if (data->proc == 0)
			child_process(data, trav);
		if (p_trav)
			close(p_trav->tab_pipe[1]);
		close(trav->tab_pipe[0]);
		close(trav->f_in);
		close(trav->f_out);
		p_trav = trav;
		trav = trav->next;
	}
	parent();
}
