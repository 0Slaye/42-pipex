/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_limiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:46:50 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/01 16:20:08 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

void	exec2(char **argv, int input_fd, int output_fd, int n)
{
	char	**split;
	char	*holder;

	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	split = ft_split(argv[n], ' ');
	if (split == NULL)
		return (ft_putstr_fd("split: An error occured\n", 2));
	holder = ft_strjoin("/bin/", split[0]);
	if (execve(holder, split, NULL) == -1)
		perror(argv[n]);
	s_free(split);
	free(holder);
}

void	parenting2(int fd)
{
	(void) fd;
	close(fd);
	wait(NULL);
}

void	childing2(int *fd, int i, char **argv, int *hfd)
{
	char	*value;
	int		fds[2];

	close(fd[0]);
	if (i == 0)
	{
		if (pipe(fds) == -1)
			return (perror("pipe"));
		while (1)
		{
			ft_putstr_fd("here_doc> ", 1);
			value = get_next_line(0);
			if (ft_strlen(argv[2]) == ft_strlen(value) -1 && ft_strncmp(argv[2], value, ft_strlen(value) - 1) == 0)
				break;
			write(fds[1], value, ft_strlen(value));
			free(value);
		}
		close(fds[1]);
		exec2(argv, fds[0], fd[1], i + 3);
	}
	else
		exec2(argv, hfd[0], fd[1], i + 3);
}

void	last_cmd2(int hfd, char **argv, int *fd, int argc)
{
	int	id;

	id = fork();
	if (id != 0)
		wait(NULL);
	else
	{
		hfd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (hfd == -1)
			return (perror("open"));
		exec2(argv, fd[0], hfd, argc - 2);
		close(hfd);
		close(fd[0]);
		close(fd[1]);
	}
}

void	pipex_limiter(int argc, char **argv)
{
	int	fd[2];
	int	hfd[2];
	int	id;
	int	i;

	i = -1;
	if (i == -1 && pipe(fd) == -1)
		return (perror("pipe"));
	while (++i != argc - 5)
	{
		hfd[0] = fd[0];
		if (i != 0 && pipe(fd) == -1)
			return (perror(argv[1]));
		id = fork();
		if (id != 0)
			parenting2(fd[1]);
		else if (id == 0)
			childing2(fd, i, argv, hfd);
		else
			return (perror("open"), exit(EXIT_FAILURE));
	}
	last_cmd2(hfd[0], argv, fd, argc);
}
