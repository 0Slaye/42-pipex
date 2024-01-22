/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:22 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/22 17:39:45 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imports.h"

int	pipex(void)
{
	return (0);
}

int main(int argc, char **argv)
{
	(void) argv;
	if (argc != 5)
		return (ft_putstr_fd("Error : wrong number of arguments.\n", 1), 0);
	else
		pipex();
	return (0);
}