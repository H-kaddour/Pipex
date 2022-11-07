/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:25:43 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/07 15:30:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(char *msg)
{
	perror(msg);
	exit(2);
}

void	add_cmd(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*head;
	t_cmd	*node;

	i = 1;
	j = 1;
	head = ft_calloc(1, sizeof(t_cmd));
	head->cmd = data->av[j++];
	head->f_in = data->f_in;
	data->cmd = head;
	while (i < data->len_args - 2)
	{
		node = ft_calloc(1, sizeof(t_cmd));
		node->cmd = data->av[j++];
		head->next = node;
		head = node;
		i++;
	}
	head->f_out = data->f_out;
}
