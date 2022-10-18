/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:03:00 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/18 17:48:10 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


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
		data.i = 0;
		data.leak = ft_calloc(1024, sizeof(char));
		processes_making(&data);
	}
	else
		perror("Check your argument!\n[program] \
				infile \"cmd 1\" \"cmd 2\" outfile");
}
