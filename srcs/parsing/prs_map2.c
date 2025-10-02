/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:01:16 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/25 17:17:34 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	borders_check(char **map, char c, size_t y, size_t x)
{
	if ((y == 0 || !map[y + 1]) && !is_wall(c))
		return (1);
	if ((x == 0 || !map[y][x + 1]) && !is_wall(c))
		return (1);
	return (0);
}

static int	placing_check(char **map, size_t y, size_t x)
{
	if ((ft_strlen(map[y - 1]) < x + 1 || map[y - 1][x] == ' ')
		|| (ft_strlen(map[y + 1]) < x + 1 || map[y + 1][x] == ' ')
		|| (map[y][x - 1] == ' ')
		|| (map[y][x + 1] == ' '))
		return (1);
	return (0);
}

int	validmap_checks(char **map, char c, size_t y, size_t x)
{
	if (borders_check(map, c, y, x))
		return (1);
	if (!is_wall(map[y][x]) && placing_check(map, y, x))
		return (1);
	return (0);
}
