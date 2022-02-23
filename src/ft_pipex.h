/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:29:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/02/21 18:22:37 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>

typedef struct pipex
{
	char	*ptr;
	char	**o_path;
	char	**flags;
	char	*n_path;
	int		fd[2];
	int		child;
	int		fdin;
	int		fdout;
}	t_end;

void	ft_pipex_it(int filein, int fileout, char **av, char **env);
void	ft_exec(char *av, char **env);
char	**ft_get_path(char **env);
char	**ft_split(char const *s, char c);
int		ft_check(char *av, char sp);
size_t	ft_strlen(const	char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
