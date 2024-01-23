/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:22 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/23 18:07:51 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

void	childing(char **argv, int fd, int fdl)
{
	char	**split;
	char	*holder;

	dup2(fd, STDIN_FILENO);
	dup2(fdl, STDOUT_FILENO);
	split = ft_split(argv[2], ' ');
	if (split == NULL)
		return (ft_putstr_fd("split: An error occured\n", 2));
	holder = ft_strjoin("/bin/", split[0]);
	if (execve(holder, split, NULL) == -1)
		perror(argv[2]);
	s_free(split);
	free(holder);
}

void	sub_parenting(char **argv, int fd, int fdl)
{
	char	**split;
	char	*holder;

	dup2(fdl, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	split = ft_split(argv[3], ' ');
	if (split == NULL)
		return (ft_putstr_fd("split: An error occured\n", 2));
	holder = ft_strjoin("/bin/", split[0]);
	if (execve(holder, split, NULL) == -1)
		perror(argv[3]);
	s_free(split);
	free(holder);
}

int	pipex(char **argv)
{
	int	fds[2];
	int	fd;
	int	id;

	if (access(argv[1], F_OK) == -1)
		return (perror(argv[1]), 1);
	if (pipe(fds) == -1)
		return (perror(argv[1]), 1);
	id = fork();
	if (id == 0)
	{
		close(fds[0]);
		fd = open(argv[1], O_RDONLY);
		id = fork();
		if (id == 0)
			childing(argv, fd, fds[1]);
		else
			return (wait(NULL), close(fds[1]), close(fd));
	}
	else
	{
		wait(NULL);
		close(fds[1]);
		fd = open(argv[4], O_CREAT | O_WRONLY, 0777);
		id = fork();
		if (id == 0)
			sub_parenting(argv, fd, fds[0]);
		else
			return (wait(NULL), close(fds[0]), close(fd));
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 5)
		return (ft_putstr_fd("Error : wrong number of arguments.\n", 1), 0);
	else
		pipex(argv);
	return (0);
}