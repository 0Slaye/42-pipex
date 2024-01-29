/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:22 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/29 17:32:15 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

int	main(int argc, char **argv)
{
	if (ft_strlen(argv[1]) == ft_strlen("here_doc") \
	&& ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex(argc, argv);
	else
		pipex(argc, argv);
	return (0);
}
