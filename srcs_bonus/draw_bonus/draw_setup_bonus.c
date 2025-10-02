/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_setup_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:01:30 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/20 16:40:41 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	draw_floor_setup(t_data *data, int y)
{
	t_draw	*draw;

	draw = &data->draw;
	draw->cf_rdirx[0] = data->player.dir[1] - data->player.fov[1];
	draw->cf_rdiry[0] = data->player.dir[0] - data->player.fov[0];
	draw->cf_rdirx[1] = data->player.dir[1] + data->player.fov[1];
	draw->cf_rdiry[1] = data->player.dir[0] + data->player.fov[0];
	draw->cf_p = y - WIN_HEIGHT / 2;
	draw->cf_posz = 0.5 * WIN_HEIGHT;
	draw->cf_dist = draw->cf_posz / draw->cf_p;
	draw->cf_step[1] = draw->cf_dist
		* (draw->cf_rdirx[1] - draw->cf_rdirx[0]) / WIN_WIDTH;
	draw->cf_step[0] = draw->cf_dist
		* (draw->cf_rdiry[1] - draw->cf_rdiry[0]) / WIN_WIDTH;
	draw->cf_floor[1] = data->player.pos[1]
		+ draw->cf_dist * draw->cf_rdirx[0];
	draw->cf_floor[0] = data->player.pos[0]
		+ draw->cf_dist * draw->cf_rdiry[0];
}

void	draw_walls_setup(char **map, t_ray ray, t_draw *draw, t_data *data)
{
	int	tmp;

	draw->height = (int)(WIN_HEIGHT / ray.w_dist);
	draw->start = -draw->height / 2 + WIN_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->w_tex[1] = (int)(ray.w_hit * (double)TEX_SIZE);
	draw->w_tex[1] = -draw->w_tex[1] + TEX_SIZE - 1;
	draw->w_step = 1.0 * TEX_SIZE / draw->height;
	draw->w_texpos = (
			(draw->start - WIN_HEIGHT / 2 + draw->height / 2) * draw->w_step);
	if (map[ray.pos[0]][ray.pos[1]] == '1')
		draw->s_wall = (mlx_get_data_addr(data->tex.wall, &tmp, &tmp, &tmp));
	else if (map[ray.pos[0]][ray.pos[1]] == '2')
		draw->s_wall = (mlx_get_data_addr(data->tex.wall2, &tmp, &tmp, &tmp));
	else if (map[ray.pos[0]][ray.pos[1]] == 'X')
		draw->s_wall = (mlx_get_data_addr(data->tex.exit, &tmp, &tmp, &tmp));
	else if (map[ray.pos[0]][ray.pos[1]] == 'D'
		&& (!data->d_anim.da_isrun || !is_lookdoor(data)))
		draw->s_wall = (mlx_get_data_addr(data->tex.doors->img,
					&tmp, &tmp, &tmp));
}

static inline void	save_draw_infos2(t_save *s_draw)
{
	s_draw->s_height = (int)(WIN_HEIGHT / s_draw->s_w_dist);
	s_draw->s_start = -s_draw->s_height / 2 + WIN_HEIGHT / 2;
	if (s_draw->s_start < 0)
		s_draw->s_start = 0;
	s_draw->s_w_tex[1] = (int)(s_draw->s_w_hit * (double)TEX_SIZE);
	s_draw->s_w_tex[1] = -s_draw->s_w_tex[1] + TEX_SIZE - 1;
	s_draw->s_w_step = 1.0 * TEX_SIZE / s_draw->s_height;
	s_draw->s_w_texpos = (
			(s_draw->s_start - WIN_HEIGHT / 2 + s_draw->s_height / 2)
			* s_draw->s_w_step);
}

void	save_draw_infos(t_data data, t_save *s_draw, void *img)
{
	int	tmp;

	s_draw->s_check = 1;
	if (data.ray.side == 0)
	{
		s_draw->s_w_dist = data.ray.dist[1] - data.ray.delta[1];
		s_draw->s_w_hit = (
				data.player.pos[0] + s_draw->s_w_dist * data.ray.dir[0]);
	}
	else
	{
		s_draw->s_w_dist = data.ray.dist[0] - data.ray.delta[0];
		s_draw->s_w_hit = (
				data.player.pos[1] + s_draw->s_w_dist * data.ray.dir[1]);
	}
	s_draw->s_w_hit -= floor(s_draw->s_w_hit);
	save_draw_infos2(s_draw);
	s_draw->s_s_img = mlx_get_data_addr(img, &tmp, &tmp, &tmp);
}
