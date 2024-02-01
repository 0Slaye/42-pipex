/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:33:33 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/01 15:15:25 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

void	pipex(int argc, char **argv);
void	pipex_limiter(int argc, char **argv);
int		split_counter(char	**value);
void	s_free(char **value);

#endif