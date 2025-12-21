/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:49:53 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/18 17:13:35 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	ray_step(t_ray *ray, t_play player)
{
	if (ray->dir[1] < 0)
	{
		ray->step[1] = -1;
		ray->dist[1] = (
				(player.pos[1] - ray->pos[1]) * ray->delta[1]);
	}
	else
	{
		ray->step[1] = 1;
		ray->dist[1] = (
				(ray->pos[1] + 1.0 - player.pos[1]) * ray->delta[1]);
	}
	if (ray->dir[0] < 0)
	{
		ray->step[0] = -1;
		ray->dist[0] = (
				(player.pos[0] - ray->pos[0]) * ray->delta[0]);
	}
	else
	{
		ray->step[0] = 1;
		ray->dist[0] = (
				(ray->pos[0] + 1.0 - player.pos[0]) * ray->delta[0]);
	}
}

void	ray_update(t_ray *ray, t_play player, int x)
{
	double	cam;

	cam = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir[1] = player.dir[1] + (player.fov[1] * cam);
	ray->dir[0] = player.dir[0] + (player.fov[0] * cam);
	ray->pos[1] = (int)player.pos[1];
	ray->pos[0] = (int)player.pos[0];
	ray->delta[1] = fabs(1 / ray->dir[1]);
	ray->delta[0] = fabs(1 / ray->dir[0]);
	ray->hit = 0;
}

void	ray_hit(t_ray *ray, t_play player)
{
	if (ray->side == 0)
	{
		ray->w_dist = ray->dist[1] - ray->delta[1];
		ray->w_hit = (
				player.pos[0] + ray->w_dist * ray->dir[0]);
	}
	else
	{
		ray->w_dist = ray->dist[0] - ray->delta[0];
		ray->w_hit = (
				player.pos[1] + ray->w_dist * ray->dir[1]);
	}
	ray->w_hit -= floor(ray->w_hit);
}

void	raycast(t_data *data, int ispreview)
{
	register int	x;
	register int	y;
	double			zbuff[WIN_WIDTH];

	x = -1;
	y = -1;
	data->ray.b_time = (double)get_current_time();
	if (!ispreview && data->tex.doors)
		handle_doors(data);
	while (++y < WIN_HEIGHT)
		(draw_floor_setup(data, y), draw_floor(data, y));
	while (++x < WIN_WIDTH)
	{
		ray_update(&data->ray, data->player, x);
		ray_step(&data->ray, data->player);
		run_dda(data, &data->ray, data->map, 1);
		ray_hit(&data->ray, data->player);
		draw_walls_setup(data->map, data->ray, &data->draw, data);
		draw_walls(data, x);
		zbuff[x] = data->ray.w_dist;
		data->d_draw.s_check = 0;
	}
	if (!ispreview)
		handle_sprites(data, zbuff);
}
