/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_draw_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:31:30 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/02 16:53:49 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static inline void	_mmap_draw_text(t_data *data, t_mmtex v)
{
	int		ws;
	char	*sw;
	int		bits[2];

	ws = data->draw.worldsize;
	sw = data->draw.s_world;
	bits[0] = (((v.yp + v.y) * ws) + ((v.xp + v.x + (64 * v.i)) * 4));
	bits[1] = ((v.y) * (64 * 4)) + (v.x * 4);
	if (v.s_tex[bits[1] + 0] != (unsigned char)0
		&& v.s_tex[bits[1] + 1] != (unsigned char)0
		&& v.s_tex[bits[1] + 2] != (unsigned char)0)
	{
		sw[bits[0] + 0] = (unsigned char)v.s_tex[bits[1] + 0];
		sw[bits[0] + 1] = (unsigned char)v.s_tex[bits[1] + 1];
		sw[bits[0] + 2] = (unsigned char)v.s_tex[bits[1] + 2];
		sw[bits[0] + 3] = (unsigned char)v.s_tex[bits[1] + 3];
	}
}

int	_draw_hp(t_data *data)
{
	register t_mmtex	v;
	int					tmp;
	int					size;

	size = 64 * 4;
	v.xp = data->menu.sm_margin;
	v.yp = WIN_HEIGHT - (2 * data->menu.sm_margin);
	v.i = -1;
	v.s_tex = mlx_get_data_addr(data->tex.heart, &tmp, &size, &tmp);
	if (!v.s_tex)
		return (1);
	while (++v.i < data->player.hp && v.i < 5)
	{
		v.x = -1;
		while (++v.x < 64)
		{
			v.y = -1;
			while (++v.y < 64)
				_mmap_draw_text(data, v);
		}
	}	
	return (0);
}

static inline void	_mmap_draw_text2(t_data *data, t_mmtex v)
{
	int		ws;
	char	*sw;
	int		bits[2];

	ws = data->draw.worldsize;
	sw = data->draw.s_world;
	bits[0] = (((v.yp + v.i) * ws) + ((v.xp + v.k) * 4));
	bits[1] = ((v.i) * v.szl1) + ((v.k) * 4);
	if (v.s_tex[bits[1] + 0] != (unsigned char)0
		&& v.s_tex[bits[1] + 1] != (unsigned char)0
		&& v.s_tex[bits[1] + 2] != (unsigned char)0)
	{
		sw[bits[0] + 0] = v.s_tex[bits[1] + 0];
		sw[bits[0] + 1] = v.s_tex[bits[1] + 1];
		sw[bits[0] + 2] = v.s_tex[bits[1] + 2];
		sw[bits[0] + 3] = v.s_tex[bits[1] + 3];
	}
}

int	_draw_key(t_data *data)
{
	register t_mmtex	v;
	int					tmp;
	int					size;

	if (data->player.keys == 0)
		return (0);
	size = 64 * 4;
	v.xp = data->menu.sm_margin;
	v.yp = data->menu.sm_margin;
	v.x = 0;
	v.y = 0;
	v.c = 1;
	v.szl1 = 64 * 4;
	v.s_tex = mlx_get_data_addr(data->tex.key[0], &tmp, &size, &tmp);
	if (!v.s_tex)
		return (1);
	v.k = 0;
	while (++v.k < 64)
	{
		v.i = 0;
		while (++v.i < 64)
			_mmap_draw_text2(data, v);
	}
	return (0);
}
