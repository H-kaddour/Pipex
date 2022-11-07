/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:54:48 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/07 14:28:44 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	get_path(t_data *data, char **env)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 5;
	while (env[i] && ft_strncmp(env[i], "PATH=", j))
		i++;
	if (!env[i])
		exit(2);
	ptr = ft_calloc(ft_strlen(&env[i][j]) + 1, sizeof(char));
	strlcpy(ptr, &env[i][j], ft_strlen(&env[i][j]) + 1);
	data->path = ft_split(ptr, ':');
}

void	execute(char *cmd, t_data *data)
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
