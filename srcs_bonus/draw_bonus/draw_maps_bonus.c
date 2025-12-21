/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_maps_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:46:54 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/16 17:02:23 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	*draw_static_title2(t_data *data, int title)
{
	if (title == 0)
	{
		data->imgl2.l2_dim[0] = data->menu.sm_dim[0];
		data->imgl2.l2_dim[1] = data->menu.sm_dim[1];
		return (data->tex.selmaps);
	}
	else if (title == 1)
	{
		data->imgl2.l2_dim[0] = data->menu.w_dim[0];
		data->imgl2.l2_dim[1] = data->menu.w_dim[1];
		return (data->tex.win);
	}
	else if (title == 2)
	{
		data->imgl2.l2_dim[0] = data->menu.l_dim[0];
		data->imgl2.l2_dim[1] = data->menu.l_dim[1];
		return (data->tex.loose);
	}
	return (NULL);
}

void	draw_static_title(t_data *data, int title)
{
	int		tmp;
	void	*tmpimg;

	tmpimg = draw_static_title2(data, title);
	data->imgl2.l2_pos[0] = data->menu.sm_margin;
	data->imgl2.l2_pos[1] = WIN_WIDTH / 2 - (data->imgl2.l2_dim[1] / 2);
	data->imgl2.s_l2 = mlx_get_data_addr(
			tmpimg, &tmp, &data->imgl2.l2_size, &tmp);
	l2draw(data, 1);
	sl2_init(&data->imgl2);
}

void	draw_back_arrow(t_data *data, int hover)
{
	int		tmp;
	void	*imgtoput;

	if (hover)
		imgtoput = data->tex.arrow_h;
	else
		imgtoput = data->tex.arrow;
	data->imgl2.l2_dim[0] = data->menu.a_dim[0];
	data->imgl2.l2_dim[1] = data->menu.a_dim[1];
	data->imgl2.l2_pos[0] = data->menu.sm_margin;
	data->imgl2.l2_pos[1] = data->imgl2.l2_pos[0];
	data->imgl2.s_l2 = mlx_get_data_addr(
			imgtoput, &tmp, &data->imgl2.l2_size, &tmp);
	l2draw(data, 1);
	sl2_init(&data->imgl2);
	mlx_put_image_to_window(data->mlx, data->win, data->draw.i_world, 0, 0);
}

void	draw_map_select(t_game *game)
{
	t_data	*data;
	int		tmp;

	data = &game->data;
	data->menu.ispaused = 5;
	data->imgl2.l2_pos[1] = WIN_WIDTH;
	data->imgl2.l2_pos[0] = WIN_HEIGHT;
	data->imgl2.s_l2 = mlx_get_data_addr(
			data->tex.menubg, &tmp, &data->imgl2.l2_size, &tmp);
	data->imgl2.l2_dim[1] = data->menu.bg_dim[1];
	data->imgl2.l2_dim[0] = data->menu.bg_dim[0];
	data->imgl2.l2_scale[1] = (
			(double)data->imgl2.l2_pos[1] / (double)data->imgl2.l2_dim[1]);
	data->imgl2.l2_scale[0] = (
			(double)data->imgl2.l2_pos[0] / (double)data->imgl2.l2_dim[0]);
	draw_resize(data, data->draw.s_world, data->draw.worldsize, 0);
	sl2_init(&data->imgl2);
	draw_static_title(&game->data, 0);
	draw_back_arrow(&game->data, 0);
	tmp = 0;
	while (tmp < 6)
		draw_previews_setup(game, tmp++, 0);
	tmp = 0;
	while (tmp < 6)
		draw_texts_setup(game, tmp++);
}
