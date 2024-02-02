/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:22 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/02 16:16:48 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

int	main(int argc, char **argv, char **envp)
{
	char	**stock[2];

	stock[0] = argv;
	stock[1] = envp;
	if (ft_strlen(argv[1]) == ft_strlen("here_doc") \
	&& ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex_limiter(argc, stock);
	else
		pipex(argc, stock);
	return (0);
}
