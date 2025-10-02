/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:33 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/13 13:31:33 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

unsigned char	blend_pixels(
		unsigned char actual_color, unsigned char toput_color, double opacity)
{
	int	final_color;

	final_color = (int)(
			(actual_color * (1.0 - opacity))
			+ (toput_color * opacity));
	if (final_color < 0)
		final_color = 0;
	else if (final_color > 255)
		final_color = 255;
	return ((unsigned char)final_color);
}

static inline void	draw_resize2(
		t_data *data, int bits, int opacity, char *s_img)
{
	t_l2			*imgl2;
	int				i;

	i = -1;
	imgl2 = &data->imgl2;
	imgl2->l2_bits = (
			(imgl2->l2_tex[0] * imgl2->l2_size) + (imgl2->l2_tex[1] * 4));
	while (opacity == 0 && ++i < 4)
	{
		s_img[bits + i] = (
				(unsigned char)data->imgl2.s_l2[data->imgl2.l2_bits + i]);
	}
	while (opacity != 0 && ++i < 4)
	{
		s_img[bits + i] = blend_pixels(
				(unsigned char)data->draw.s_world[bits + i],
				(unsigned char)data->imgl2.s_l2[data->imgl2.l2_bits + i],
				PAUSE_OPACITY);
	}
}

void	draw_resize(t_data *data, char *s_img, int imgsize, int opacity)
{
	int	x;
	int	y;
	int	bits;

	x = 0;
	if (data->is_end != 0)
		opacity = 0;
	while (x < data->imgl2.l2_pos[1])
	{
		y = 0;
		data->imgl2.l2_tex[1] = x / data->imgl2.l2_scale[1];
		while (y < data->imgl2.l2_pos[0])
		{
			bits = (y * imgsize) + (x * 4);
			data->imgl2.l2_tex[0] = y / data->imgl2.l2_scale[0];
			draw_resize2(data, bits, opacity, s_img);
			y++;
		}
		x++;
	}
}

int	menu_setup(t_data *data, int ispause)
{
	int	tmp;

	if (ispause == 2 && data->menu.ispaused == 3)
		return (resume_game(data), 0);
	data->menu.ispaused = ispause + 1;
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
	draw_resize(data, data->draw.s_world, data->draw.worldsize, ispause);
	mlx_put_image_to_window(data->mlx, data->win, data->draw.i_world, 0, 0);
	mlx_mouse_show(data->mlx, data->win);
	sl2_init(&data->imgl2);
	if (data->is_end == 0)
		(opts_setup(data, ispause + 1, 0), opts_setup(data, ispause + 2, 0));
	else
		(opts_setup(data, ispause + 2, 0),
			draw_static_title(data, data->is_end));
	return (0);
}

void	resume_game(t_data *data)
{
	mlx_mouse_hide(data->mlx, data->win);
	data->menu.ispaused = 0;
}
