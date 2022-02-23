/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:46 by hkaddour          #+#    #+#             */
/*   Updated: 2022/02/21 15:38:17 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	ft_strcount(char *s, char c)
{
	int	len;

	len = 0;
	while (*s != '\0')
	{
		if (*s != c && *s)
		{
			len++;
			while (*s != '\0' && *s != c)
				s++;
			continue ;
		}
		s++;
	}
	return (len);
}

static char	*ft_alloc_word_by_word(char *s, char c)
{
	int		len;
	char	*ptr;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	ptr = (char *) malloc(sizeof(char) * len + 1);
	while (*s != c && *s)
	{
		*ptr++ = *s++;
	}
	*ptr = '\0';
	return (ptr - len);
}

static void	ft_alloc_all(char *str, char c, int w, char **ptr)
{
	while (*str)
	{
		if (*str != c && *str)
		{
			ptr[w++] = ft_alloc_word_by_word(str, c);
			if (!ptr)
			{
				while (w >= 0)
				{
					free(ptr[w--]);
				}
				free(ptr);
			}
			while (*str != c && *str)
				str++;
			continue ;
		}
		str++;
	}
	ptr[w] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		w;
	char	**ptr;
	char	*str;

	i = 0;
	w = 0;
	if (!s)
		return (NULL);
	str = (char *) s;
	ptr = (char **) malloc(sizeof(char *) * (ft_strcount(str, c) + 1));
	if (!ptr)
		return (NULL);
	ft_alloc_all(str, c, w, ptr);
	return (ptr);
}
