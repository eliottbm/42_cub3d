/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:49:53 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/11 14:08:40 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	run_dda(t_ray *ray, char **map)
{
	while (!ray->hit)
	{
		if (ray->dist[1] < ray->dist[0])
		{
			ray->dist[1] += ray->delta[1];
			ray->pos[1] += ray->step[1];
			ray->side = 0;
		}
		else
		{
			ray->dist[0] += ray->delta[0];
			ray->pos[0] += ray->step[0];
			ray->side = 1;
		}
		if (map[ray->pos[0]][ray->pos[1]] == '1')
			ray->hit = 1;
	}
}

static void	ray_step(t_ray *ray, t_play player)
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

static void	ray_update(t_ray *ray, t_play player, int x)
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
	ray->tdir = NONE;
}

static void	ray_hit(t_ray *ray, t_play player)
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
	if (ray->side == 0 && (player.pos[1] - ray->pos[1]) > 0)
		ray->tdir = EAST;
	else if (ray->side == 0)
		ray->tdir = WEST;
	else if (ray->side == 1 && (player.pos[0] - ray->pos[0]) > 0)
		ray->tdir = SOUTH;
	else
		ray->tdir = NORTH;
}

void	raycast(t_data *data)
{
	int	x;

	x = 0;
	data->ray.b_time = (double)get_current_time();
	while (x < WIN_WIDTH)
	{
		ray_update(&data->ray, data->player, x);
		ray_step(&data->ray, data->player);
		run_dda(&data->ray, data->map);
		ray_hit(&data->ray, data->player);
		draw_setup(data->ray, &data->draw, data->tex);
		draw_world(*data, &data->draw, x);
		x++;
	}
	mlx_put_image_to_window(
		data->mlx, data->win, data->draw.i_world, 0, 0);
	calc_fps(data);
}
