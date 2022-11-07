/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:03:00 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/07 14:31:04 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac == 5)
	{
		data.f_in = open(av[1], O_RDONLY);
		if (data.f_in < 0)
			perror("file in fails to read :(\n");
		data.f_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (data.f_out < 0)
			perror("file out fails to create :(\n");
		data.av = &av[1];
		data.env = env;
		processes_making(&data);
	}
	else
		perror("Check your argument!\n");
}
