/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:30 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/19 10:21:45 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_line(char *str, t_gnl *t_line)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[0] == '\0')
		return (NULL);
	t_line->ptr = malloc(sizeof(char) * i);
	if (!t_line->ptr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		t_line->ptr[i] = str[i];
		i++;
	}
	t_line->ptr[i] = 0;
	return (t_line->ptr);
}

static char	*next_line(char *str)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * 1);
	ptr[0] = 0;
	free(str);
	return (ptr);
}

static int	newline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static char	*read_line(char *str, int fd, t_gnl *t_line)
{
	int		i;

	i = 1;
	while (i != 0)
	{
		i = read(fd, t_line->buff, 1);
		if (i == -1)
		{
			free(t_line->buff);
			return (NULL);
		}
		t_line->buff[i] = 0;
		t_line->tmp = str;
		if (!t_line->tmp)
		{
			t_line->tmp = malloc(sizeof(char) * 1);
			t_line->tmp[0] = 0;
		}
		str = ft_strjoin(t_line->tmp, t_line->buff);
		free(t_line->tmp);
		if (newline(str) == 1)
			break ;
	}
	free(t_line->buff);
	return (str);
}

char	*grab_line(int fd)
{
	static char	*str;
	t_gnl		t_line;

	if (fd < 0)
		return (NULL);
	t_line.buff = malloc(sizeof(char) * 2);
	if (!t_line.buff)
		return (NULL);
	str = read_line(str, fd, &t_line);
	if (!str)
		return (NULL);
	t_line.line = get_line(str, &t_line);
	str = next_line(str);
	return (t_line.line);
}
