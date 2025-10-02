/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_vision_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:15:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/28 17:42:56 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static unsigned char	_pixel_fusion(
		t_data *data, int bits, int incrb, unsigned char color)
{
	unsigned char	toput_color;
	int				final_color;
	int				actual_color;

	toput_color = color;
	actual_color = (unsigned char)data->draw.s_world[bits + incrb];
	final_color = (int)(
			(actual_color) * (1.0 - MMAP_OPACITY)
			+ (toput_color * MMAP_OPACITY));
	if (final_color < 0)
		final_color = 0;
	else if (final_color > 255)
		final_color = 255;
	return ((unsigned char)final_color);
}

static void	_draw_vector2(t_data *data, t_mmtex *v, int color)
{
	int		ws;
	char	*sw;
	int		bits;

	ws = data->draw.worldsize;
	sw = data->draw.s_world;
	bits = ((v->yp - (((v->x))) + v->i) * ws)
		+ ((v->xp + ((v->y)) + v->k) * 4);
	sw[bits + 0] = _pixel_fusion(data, bits, 0, ((color >> 16) & 0xFF));
	sw[bits + 1] = _pixel_fusion(data, bits, 1, ((color >> 8) & 0xFF));
	sw[bits + 2] = _pixel_fusion(data, bits, 1, ((color & 0xFF)));
	sw[bits + 3] = _pixel_fusion(data, bits, 1, ((color >> 24) & 0xFF));
}

static void	_draw_vector(t_data *data, double vector[2], int color)
{
	t_mmtex		v;
	double		step[2];
	double		step2[2];

	step[0] = -vector[0];
	step[1] = vector[1];
	step2[0] = step[0];
	step2[1] = step[1];
	v.i = 0;
	v.k = 0;
	v.x = 47;
	v.y = 78;
	v.yp = WIN_HEIGHT - (WIN_HEIGHT / PX_MMAP);
	v.xp = WIN_WIDTH - (WIN_WIDTH / PY_MMAP);
	while (((int)ft_pow2(fabs(step2[0])) + ft_pow2((int)fabs(step2[1])))
		<= ft_pow2(78))
	{
		_draw_vector2(data, &v, color);
		step2[0] += step[0];
		step2[1] += step[1];
		v.k = (int)floor(step2[1]);
		v.i = (int)floor(step2[0]);
	}
	return ;
}

void	_draw_vector_group(t_data *data)
{
	int		x;
	double	vector[2];
	int		color;
	double	cam;

	x = 0;
	color = encode_color(M_B, M_G, M_R, 0);
	while (x < WIN_WIDTH)
	{
		cam = 2 * x / (double)WIN_WIDTH - 1;
		vector[1] = data->player.dir[1] + (data->player.fov[1] * cam);
		vector[0] = data->player.dir[0] + (data->player.fov[0] * cam);
		_draw_vector(data, vector, color);
		x++;
	}
}
