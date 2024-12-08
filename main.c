/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:54:20 by modavid           #+#    #+#             */
/*   Updated: 2024/11/11 21:41:08 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_in_env(char *cmd, char *PATH)
{
	char	**tab;
	int		i;
	char	*res;

	tab = ft_split(PATH + 5, ':');
	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		tab[i] = ft_strjoin(tab[i], "/");
		tab[i] = ft_strjoin(tab[i], cmd);
		if (access(tab[i], X_OK) == 0)
			break ;
	}
	if (tab[i] == NULL)
		return (ft_free_all(tab), NULL);
	res = ft_strdup(tab[i]);
	return (ft_free_all(tab), res);
}

char	*find_path(char *av, char **env)
{
	int		i;

	if (access(av, X_OK) == 0)
		return (ft_strdup(av));
	if (!env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		if (!env[i])
			return (NULL);
	}
	return (find_in_env(av, env[i]));
}

void	ft_exec(char *av, char **env, int infile, int outfile)
{
	char	*path;
	char	**cmd;
	int		i;

	i = 1;
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	cmd = ft_split(av, ' ');
	if (!cmd)
		exit(1);
	if (!cmd[0])
		return (ft_free_all(cmd), ft_putendl_fd("Empty line", 2), exit(1));
	path = find_path(cmd[0], env);
	if (!path)
		return (ft_free_all(cmd), ft_putendl_fd("Command not found", 2),
			exit(127));
	if (execve(path, cmd, env) == -1)
	{
		perror(cmd[0]);
		ft_free_all(cmd);
		free(path);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	pid_t	pid[2];
	int		fd;
	int		pipefd[2];

	if (ac != 5)
		return (1);
	i = 0;
	pipe(pipefd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pipefd[0]);
		fd = ft_open(av[1], O_RDONLY, pipefd[1]);
		ft_exec(av[2], env, fd, pipefd[1]);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(pipefd[1]);
		fd = ft_open(av[4], O_WRONLY | O_CREAT | O_TRUNC, pipefd[0]);
		ft_exec(av[3], env, pipefd[0], fd);
	}
	return (close_and_wait(pipefd, pid));
}
