/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:46:50 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/23 22:17:24 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

void	exec(char **argv, int input_fd, int output_fd, int n)
{
	char	**split;
	char	*holder;

	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	split = ft_split(argv[n], ' ');
	if (split == NULL)
		return (ft_putstr_fd("split: An error occured\n", 2));
	holder = ft_strjoin("/bin/", split[0]);
	if (execve(holder, split, NULL) == -1)
		perror(argv[n]);
	s_free(split);
	free(holder);
}

void	pipex(int argc, char **argv)
{
	int	pfd[2];
	int	holder;
	int	id;
	int	fd;
	int	i;

	if (pipe(pfd) == -1)
		return (perror(argv[1]));
	holder = pfd[0];
	i = -1;
	while (++i != argc - 4)
	{
		id = fork();
		if (id != 0)
		{
			close(pfd[1]);
			wait(NULL);
		}
		else
		{
			if (i == 0)
			{
				close(pfd[0]);
				holder = open(argv[1], O_RDONLY);
			}
			id = fork();
			if (id == 0)
			{
				if (i == 0)
					exec(argv, holder, pfd[1], i + 2);
				else
					exec(argv, pfd[0], pfd[1], i + 2);
			}
			else
				return (wait(NULL), close(holder), close(pfd[0]), close(pfd[1]), (void) NULL);
		}
	}
	fd = open(argv[argc - 1], O_CREAT | O_WRONLY, 0777);
	id = fork();
	if (id == 0)
		exec(argv, pfd[0], fd, argc - 2);
	else
		return (wait(NULL), close(pfd[0]), close(pfd[1]), close(fd), (void) NULL);
}
