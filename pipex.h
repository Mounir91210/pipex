/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:55:00 by modavid           #+#    #+#             */
/*   Updated: 2024/11/11 21:19:09 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_data
{
	char	**path;
}	t_data;

int		ft_open(char *file, int options, int fd_to_close);
int		close_and_wait(int *pipefd, int *pid);
char	*find_in_env(char *cmd, char *PATH);
char	*find_path(char *av, char **env);
void	ft_exec(char *av, char **env, int infile, int outfile);

#endif