/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:54:48 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/18 18:07:14 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i])
		free(data->path[i++]);
	free(data->path);
	i = 0;
	while (data->leak[i])
		free(data->leak[i++]);
	free(data->leak);
}

char *add_join(t_data *data, char *path, char *cmd)
{
	char	*ptr;

	ptr = ft_strjoin(path, cmd);
	data->leak[data->i++] = ptr;
	return (ptr);
}

void	get_path(t_data *data, char **env)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 5;
	while (env[i] && ft_strncmp(env[i], "PATH=", j))
		i++;
	ptr = ft_calloc(ft_strlen(&env[i][j]) + 1, sizeof(char));
	data->leak[data->i++] = ptr;
	strlcpy(ptr, &env[i][j], ft_strlen(&env[i][j]) + 1);
	data->path = ft_split(ptr, ':');
}
