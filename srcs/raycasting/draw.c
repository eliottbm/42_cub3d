/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:01:30 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/20 17:05:34 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_setup(t_ray ray, t_draw *draw, t_tex tex)
{
	void	*wall;
	int		tmp;

	draw->height = (int)(WIN_HEIGHT / ray.w_dist);
	draw->start = -draw->height / 2 + WIN_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->tex[1] = (int)(ray.w_hit * (double)TEX_SIZE);
	if (ray.tdir != SOUTH)
		draw->tex[1] = -draw->tex[1] + TEX_SIZE - 1;
	draw->step = 1.0 * TEX_SIZE / draw->height;
	draw->pos = (
			(draw->start - WIN_HEIGHT / 2 + draw->height / 2)
			* draw->step);
	wall = tex.no;
	if (ray.tdir == EAST)
		wall = tex.ea;
	else if (ray.tdir == SOUTH)
		wall = tex.so;
	else if (ray.tdir == WEST)
		wall = tex.we;
	draw->s_wall = (
			mlx_get_data_addr(wall, &tmp, &draw->wallsize, &tmp));
}

static void	draw_wall(t_draw *draw, int imgbits)
{
	int	wallbits;

	wallbits = (draw->tex[0] * draw->wallsize) + (draw->tex[1] * 4);
	draw->s_world[imgbits + 0] = draw->s_wall[wallbits + 0];
	draw->s_world[imgbits + 1] = draw->s_wall[wallbits + 1];
	draw->s_world[imgbits + 2] = draw->s_wall[wallbits + 2];
	draw->s_world[imgbits + 3] = draw->s_wall[wallbits + 3];
}

static void	draw_cf(int color, t_draw *draw, int imgbits)
{
	if (draw->worldend)
	{
		draw->s_world[imgbits + 0] = (color >> 24);
		draw->s_world[imgbits + 1] = (color >> 16) & 0xFF;
		draw->s_world[imgbits + 2] = (color >> 8) & 0xFF;
		draw->s_world[imgbits + 3] = (color) & 0xFF;
	}
	else
	{
		draw->s_world[imgbits + 0] = (color) & 0xFF;
		draw->s_world[imgbits + 1] = (color >> 8) & 0xFF;
		draw->s_world[imgbits + 2] = (color >> 16) & 0xFF;
		draw->s_world[imgbits + 3] = (color >> 24);
	}
}

void	draw_world(t_data data, t_draw *draw, int x)
{
	int	bits;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		bits = ((draw->worldsize * y) + (x * 4));
		if (y < draw->start)
			draw_cf(data.tex.c, draw, bits);
		else if (y >= draw->start + draw->height)
			draw_cf(data.tex.f, draw, bits);
		else
		{
			draw->tex[0] = (int)draw->pos;
			draw_wall(draw, bits);
			draw->pos += draw->step;
		}
		y++;
	}
}
