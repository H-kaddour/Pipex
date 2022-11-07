/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:21:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/07 15:34:15 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	check_if_heredoc(t_data *data)
{
	if (!ft_strncmp(data->av[0], "here_doc", ft_strlen(data->av[0])))
		return (1);
	return (0);
}

static void	free_cmd_lst(t_data *data)
{
	t_cmd	*trav;
	
	trav = data->cmd;
	while (trav)
	{
		free(trav->tab_pipe);
		trav = trav->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac >= 5)
	{
		data.len_args = ac - 1;
		data.av = &av[1];
		data.env = env;
		if (check_if_heredoc(&data))
			run_heredoc(&data);
		else
			pipeline(&data);
		free_cmd_lst(&data);
	}
	else
		perror("Check your argument!\n");
}
