/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:21:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/21 15:57:49 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_if_heredoc(t_data *data)
{
	if (!ft_strncmp(data->av[0], "here_doc", ft_strlen(data->av[0])))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	if (ac >= 5)
	{
		data.len_args = ac - 1;
		data.av = &av[1];
		data.env = env;
		//if (check_if_heredoc(&data))
		//	run_heredoc(&data);
		//else
			pipeline(&data);
	}
	else
		perror("Check your argument!\n \
				[program] infile \"cmd 1\" \"cmd 2\" outfile");
}
