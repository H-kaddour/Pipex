/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:34:23 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/21 22:02:43 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(t_data *data)
{
	//if error in file opening exit the program
	data->f_in = open(data->av[0], O_RDONLY);
	if (data->f_in < 0)
		perror("file in fails to read :(\n");
	data->f_out = open(data->av[data->len_args - 1], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (data->f_out < 0)
		perror("file out fails to create :(\n");
}

void	pipeline(t_data *data)
{
	int	i;
	int	*tab_pipe;
	int	len_cmd;
	int	cmd_pos;

	i = 0;
	len_cmd = data->len_args - 2;
	open_files(data);
	tab_pipe = malloc(sizeof(int) * (len_cmd - 1) * 2);
	if (!tab_pipe)
		return ;
	while (i < (len_cmd - 1) * 2)
	{
		if (pipe(data->fd) < 0)
		{
			perror("Error in pipe\n");
			exit(1);
		}
		tab_pipe[i++] = data->fd[1];
		tab_pipe[i++] = data->fd[0];
	}
	i = 0;
	cmd_pos = 1;
	while (i < len_cmd)
	{
		data->proc = fork();
		if (data->proc < 0)
		{
			perror("Error in fork\n");
			exit(1);
		}
		if (data->proc == 0)
		{
			//in
			if (i == 0)
			{
				dup2(data->f_in, STDIN_FILENO);
				close(data->f_in);
			}
			else
			{
				if (i % 2 == 0)
				{
					dup2(tab_pipe[i + 1], STDIN_FILENO);
					close(tab_pipe[i]);
					//close(tab_pipe[i + 1]);
				}
				else
				{
					dup2(tab_pipe[i], STDIN_FILENO);
					//close(tab_pipe[i]);
					//close(tab_pipe[i + 1]);
				}
			}
			//out
			if (i != len_cmd - 1)
			{
				if (i % 2 == 0)
				{
					dup2(tab_pipe[i], STDOUT_FILENO);
					//close(tab_pipe[i]);
					//close(tab_pipe[i + 1]);
				}
				else
				{
					dup2(tab_pipe[i + 1], STDOUT_FILENO);
					//close(tab_pipe[i]);
					//close(tab_pipe[i + 1]);
				}
			}
			else
			{
				dup2(data->f_out, STDOUT_FILENO);
				//*close(data->f_out);
				//close(tab_pipe[i]);
			}
			//
			execute(data->av[cmd_pos], data);
		}
		close(tab_pipe[i]);
		//printf("out loop %d\n ", tab_pipe[i]);
		//close(tab_pipe[i + 1]);
		cmd_pos++;
		i++;
	}
	while (1)
	{
		if (waitpid(-1, 0, 0) == -1)
			break ;
	}
}




//	while (i < data->len_args - 2)
//	{
//		if (pipe(data->fd) < 0)
//		{
//			perror("Error in pipe\n");
//			exit(1);
//		}
//		pid = fork();
//		if (pid < 0)
//		{
//			perror("fork: Resource temporarily unavailable\n");
//			exit(1);
//		}
//		if (pid == 0)
//		{
//			close(data->fd[0]);
//			dup2(hld_fd, STDIN_FILENO);
//			if (i != data->len_args)
//				dup2(data->fd[1], STDOUT_FILENO);
//			else
//				dup2(data->f_out, STDOUT_FILENO);
//			//close(data->fd[1]);
//			execute(data->av[cmd_pos], data);
//		}
//		if (pid > 0)
//		{
//			waitpid(-1, 0, 0);
//			//close(data->fd[0]);
//			close(data->fd[1]);
//			hld_fd = data->fd[0];
//			cmd_pos++;
//			i++;
//		}
//		//cmd_pos++;
//		//i++;
//	}
//	//while (21)
//	//{
//	//	waitpid(-1, 0, 0);
//	//	//wait(0);
//	//	//close(data->fd[0]);
//	//	close(data->fd[1]);
//	//	hld_fd = data->fd[0];
//	//	//if (waitpid(-1, 0, 0) == -1)
//	//	//{
//	//	//close(data->fd[0]);
//	//	//close(data->fd[1]);
//	//	//hld_fd = data->fd[0];
//	//	//	break ;
//	//	//}
//	//	//close(data->fd[1]);
//	//	//hld_fd = data->fd[0];
//	//}
