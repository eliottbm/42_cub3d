/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:01:30 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/02 17:47:17 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static inline void	draw_w(t_data *data, int bits)
{
	t_draw	*draw;
	int		sbits;
	double	fog;

	draw = &data->draw;
	draw->w_tex[0] = (int)draw->w_texpos;
	sbits = (draw->w_tex[0] * TEX_SIZE * 4) + (draw->w_tex[1] * 4);
	fog = fmax(0.0, 1.0 - (data->ray.w_dist / FOG_DIST));
	draw->s_world[bits + 0] = (
			(unsigned char)data->draw.s_wall[sbits + 0]) * fog;
	draw->s_world[bits + 1] = (
			(unsigned char)data->draw.s_wall[sbits + 1]) * fog;
	draw->s_world[bits + 2] = (
			(unsigned char)data->draw.s_wall[sbits + 2]) * fog;
	draw->s_world[bits + 3] = (
			(unsigned char)data->draw.s_wall[sbits + 3]) * fog;
	draw->w_texpos += draw->w_step;
}

static inline void	draw_d(t_data *data, t_save *saved, int bits)
{
	int		sbits;
	double	fog;

	saved->s_w_tex[0] = (int)saved->s_w_texpos;
	sbits = (saved->s_w_tex[0] * TEX_SIZE * 4)
		+ (saved->s_w_tex[1] * 4);
	if (saved->s_s_img[sbits] != 0 && saved->s_s_img[sbits + 1] != 0
		&& saved->s_s_img[sbits + 2] != 0)
	{
		fog = fmax(0.0, 1.0 - (saved->s_w_dist / FOG_DIST));
		data->draw.s_world[bits + 0] = (
				(unsigned char)saved->s_s_img[sbits + 0]) * fog;
		data->draw.s_world[bits + 1] = (
				(unsigned char)saved->s_s_img[sbits + 1]) * fog;
		data->draw.s_world[bits + 2] = (
				(unsigned char)saved->s_s_img[sbits + 2]) * fog;
		data->draw.s_world[bits + 3] = (
				(unsigned char)saved->s_s_img[sbits + 3]) * fog;
	}
	saved->s_w_texpos += saved->s_w_step;
}

void	draw_walls(t_data *data, int x)
{
	int	bits;
	int	y;
	int	end;

	if (data->d_draw.s_check > 0 && !data->d_anim.da_isdone)
	{
		y = ft_min(data->d_draw.s_start, data->draw.start);
		end = ft_max(y + data->d_draw.s_height, y + data->draw.height);
	}
	else
	{
		y = data->draw.start;
		end = data->draw.start + data->draw.height;
	}
	while (y < end && y <= WIN_HEIGHT)
	{
		bits = ((data->draw.worldsize * y) + (x * 4));
		if (y >= data->draw.start && y < data->draw.start + data->draw.height)
			draw_w(data, bits);
		if (data->d_draw.s_check > 0 && !data->d_anim.da_isdone
			&& y >= data->d_draw.s_start
			&& y < data->d_draw.s_start + data->d_draw.s_height)
			draw_d(data, &data->d_draw, bits);
		y++;
	}
}

static inline void	draw_cf(t_data *data, int bits, int sbits, char *s_img)
{
	double	fog;

	fog = fmax(0.0, 1.0 - (data->draw.cf_dist / FOG_DIST));
	data->draw.s_world[bits + 0] = (unsigned char)s_img[sbits + 0] * fog;
	data->draw.s_world[bits + 1] = (unsigned char)s_img[sbits + 1] * fog;
	data->draw.s_world[bits + 2] = (unsigned char)s_img[sbits + 2] * fog;
	data->draw.s_world[bits + 3] = (unsigned char)s_img[sbits + 3] * fog;
}

void	draw_floor(t_data *data, int y)
{
	int	x;
	int	sbits;

	x = 0;
	while (x < WIN_WIDTH)
	{
		data->draw.cf_cell[1] = (int)data->draw.cf_floor[1];
		data->draw.cf_cell[0] = (int)data->draw.cf_floor[0];
		data->draw.cf_texpos[1] = (int)(TEX_SIZE * (data->draw.cf_floor[1]
					- data->draw.cf_cell[1])) & (TEX_SIZE - 1);
		data->draw.cf_texpos[0] = (int)(TEX_SIZE * (data->draw.cf_floor[0]
					- data->draw.cf_cell[0])) & (TEX_SIZE - 1);
		sbits = (64 * 4 * data->draw.cf_texpos[0])
			+ (data->draw.cf_texpos[1] * 4);
		data->draw.cf_floor[1] += data->draw.cf_step[1];
		data->draw.cf_floor[0] += data->draw.cf_step[0];
		draw_cf(data, ((data->draw.worldsize * y) + (x * 4)),
			sbits, data->draw.s_floor);
		draw_cf(data, ((data->draw.worldsize * (WIN_HEIGHT - y - 1)) + (x * 4)),
			sbits, data->draw.s_ceil);
		x++;
	}
}
