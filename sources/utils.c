/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:22 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/29 17:23:29 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

int	split_counter(char **value)
{
	int	i;

	i = -1;
	while (value[i] != NULL)
		i++;
	return (i);
}

void	s_free(char **value)
{
	int	i;

	i = -1;
	while (value[++i] != NULL)
		free(value[i]);
	free(value);
}
