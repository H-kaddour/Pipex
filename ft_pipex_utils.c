/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:54:48 by hkaddour          #+#    #+#             */
/*   Updated: 2022/02/21 18:20:12 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

size_t	ft_strlen(const	char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str1;
	char	*str2;
	char	*ptr;

	str1 = (char *) s1;
	str2 = (char *) s2;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	ptr = malloc(sizeof(char ) * len + 1);
	if (ptr == NULL)
		return (NULL);
	while (*str1)
		*ptr++ = *str1++;
	*ptr++ = '/';
	while (*str2)
		*ptr++ = *str2++;
	*ptr = 0;
	return ((char *) ptr - len);
}

int	ft_check(char *av, char sp)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	while (av[i] != '\0')
	{
		if (av[i] == sp)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i])
		i++;
	return ((unsigned char ) s1[i] - (unsigned char ) s2[i]);
}

char	**ft_get_path(char **env)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;
	char	**arr;

	i = 0;
	j = 5;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	while (env[i][j] != '\0')
		j++;
	ptr = (char *) malloc(sizeof(char) * j + 1);
	if (!ptr)
		return (NULL);
	j = 0;
	k = 5;
	while (env[i][j] != '\0')
		ptr[j++] = env[i][k++];
	ptr[j] = 0;
	arr = ft_split(ptr, ':');
	return (arr);
}
