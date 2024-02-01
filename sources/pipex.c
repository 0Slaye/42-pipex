/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:46:50 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/01 16:14:09 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

void	exec(char **argv, int input_fd, int output_fd, int n)
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

void	parenting(int fd)
{
	(void) fd;
	close(fd);
	wait(NULL);
}

void	childing(int *fd, int i, char **argv, int *hfd)
{
	close(fd[0]);
	if (i == 0)
		exec(argv, hfd[1], fd[1], i + 2);
	else
		exec(argv, hfd[0], fd[1], i + 2);
}

void	last_cmd(int hfd, char **argv, int *fd, int argc)
{
	int	id;

	id = fork();
	if (id != 0)
		wait(NULL);
	else
	{
		hfd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (hfd == -1)
			return (perror("open"));
		exec(argv, fd[0], hfd, argc - 2);
		close(hfd);
		close(fd[0]);
		close(fd[1]);
	}
}

void	pipex(int argc, char **argv)
{
	int	fd[2];
	int	hfd[2];
	int	id;
	int	i;

	i = -1;
	if (i == -1 && pipe(fd) == -1)
		return (perror(argv[1]));
	while (++i != argc - 4)
	{
		hfd[0] = fd[0];
		if (i != 0 && pipe(fd) == -1)
			return (perror(argv[1]));
		if (i == 0)
			hfd[1] = open(argv[1], O_RDONLY);
		id = fork();
		if (id != 0)
			parenting(fd[1]);
		else if (id == 0 && hfd[1] != -1)
			childing(fd, i, argv, hfd);
		else
			return (perror("open"), exit(EXIT_FAILURE));
	}
	last_cmd(hfd[0], argv, fd, argc);
}
