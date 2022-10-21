/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:53:30 by hkaddour          #+#    #+#             */
/*   Updated: 2021/12/02 11:47:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_int_min(void)
{
	char	*ptr;

	ptr = malloc (sizeof(char) * (12));
	ft_strlcpy(ptr, "-2147483648", 12);
	return (ptr);
}

static char	*ft_alloc(int n, int i, char **ptr)
{
	if (n >= 0)
		*ptr = malloc(sizeof(char) * i + 1);
	if (n < 0)
		*ptr = malloc (i + 2);
	if (!*ptr)
		return (NULL);
	return (0);
}

static int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*ptr;

	i = ft_nbrlen(n);
	if (n == -2147483648)
		return (ft_int_min());
	ft_alloc(n, i, &ptr);
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		i++;
		n = -n;
		ptr[0] = '-';
	}
	ptr[i] = '\0';
	i--;
	while (n > 9)
	{
		ptr[i--] = n % 10 + '0';
		n /= 10;
	}
	ptr[i] = n + '0';
	return (ptr);
}
