/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:54:20 by modavid           #+#    #+#             */
/*   Updated: 2024/11/11 21:15:04 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open(char *file, int options, int fd_to_close)
{
	int	fd;

	fd = open(file, options, 0644);
	if (fd == -1)
	{
		perror(file);
		close(fd_to_close);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	close_and_wait(int *pipefd, int *pid)
{
	int	status;

	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}
