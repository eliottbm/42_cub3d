/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:52:23 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/19 17:48:57 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	_mmap_key_handle(t_data *data, int (pos)[2])
{
	if (_mmap_draw_pixel(data, pos, data->tex.floor, 0))
		return (1);
	if (_mmap_draw_pixel(data, pos, data->tex.key[0], 1))
		return (1);
	return (0);
}

static inline void	_mmap_draw_loop2(char c, void **text, t_data *data)
{
	if (c == '-' || c == '1' || c == '2')
		*text = data->tex.ceil;
	if (c == 'P' || c == '0' || c == 'G')
		*text = data->tex.floor;
	if (c == 'D')
		*text = data->tex.doors->img;
	if (c == 'X')
		*text = data->tex.exit;
}

static inline int	_mmap_draw_loop(t_data *data, char **map)
{
	int		p[2];
	void	*text;
	char	c;

	p[0] = -1;
	while (map[++p[0]])
	{
		p[1] = -1;
		while (map[p[0]][++p[1]])
		{
			c = map[p[0]][p[1]];
			_mmap_draw_loop2(c, &text, data);
			if (c == 'K')
				_mmap_key_handle(data, p);
			else if (_mmap_draw_pixel(data, p, text, 0))
				return (1);
		}
	}
	return (0);
}

int	_mmap_draw(t_data *data, char **map)
{
	if (_mmap_draw_loop(data, map))
		return (1);
	_draw_vector_group(data);
	if (_draw_player(data) || _draw_overlay(data)
		|| _draw_hp(data) || _draw_key(data))
		return (1);
	return (0);
}
