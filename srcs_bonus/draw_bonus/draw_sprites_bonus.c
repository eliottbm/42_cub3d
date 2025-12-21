/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:01:30 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/20 16:42:21 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static inline void	draw_sprites3(t_data *data, int bits,
	int sbits, t_sprites *sprites)
{
	double	fog;
	int		i;

	i = -1;
	if (sprites->sp_k_or_g == 'K')
	{
		fog = fmax(0.0, 1.0 - (sprites->sp_dist / FOG_DIST));
		while (++i < 4)
			data->draw.s_world[bits + i] = (
					(unsigned char)sprites->sp_s_img[sbits + i] * fog);
	}
	else
	{
		if (sprites->sp_dist > 2.0)
			fog = fmax(0.0, 1.0 - (sprites->sp_dist / (FOG_DIST + 3)));
		else
			fog = 1.0;
		while (++i < 4)
			data->draw.s_world[bits + i] = blend_pixels(
					(unsigned char)data->draw.s_world[bits + i],
					(unsigned char)sprites->sp_s_img[sbits + i], fog);
	}
}

static inline void	draw_sprites2(t_data *data, t_dsprites *dsp,
	int x, t_sprites *sprites)
{
	int		y;
	int		bits;
	int		sbits;

	y = dsp->sp_drawy[0];
	while (y < dsp->sp_drawy[1])
	{
		dsp->sp_d = (y - dsp->vmovescreen) * 256 - WIN_HEIGHT
			* 128 + dsp->sp_height * 128;
		dsp->sp_texpos[0] = ((dsp->sp_d * TEX_SIZE) / dsp->sp_height) / 256;
		sbits = (dsp->sp_texpos[0] * TEX_SIZE * 4) + (dsp->sp_texpos[1] * 4);
		bits = ((data->draw.worldsize * y) + (x * 4));
		if (sprites->sp_s_img[sbits] != 0
			&& sprites->sp_s_img[sbits + 1] != 0
			&& sprites->sp_s_img[sbits + 2] != 0)
			draw_sprites3(data, bits, sbits, sprites);
		y++;
	}
}

static inline void	draw_sprites(t_data *data, t_dsprites *dsp,
	t_sprites *sprites, double zbuff[WIN_WIDTH])
{
	int	x;

	x = dsp->sp_drawx[0];
	while (x < dsp->sp_drawx[1])
	{
		dsp->sp_texpos[1] = (int)(256 * (x - (-dsp->sp_width / 2
						+ dsp->sp_screen[1])) * TEX_SIZE / dsp->sp_width) / 256;
		if (dsp->transform[0] > 0 && x > 0 && x < WIN_WIDTH
			&& dsp->transform[0] < zbuff[x])
			draw_sprites2(data, dsp, x, sprites);
		x++;
	}
}

static inline void	draw_sprites_setup2(t_dsprites *dsp, t_sprites *sprites)
{
	dsp->sp_drawy[0] = (-dsp->sp_height / 2)
		+ (WIN_HEIGHT / 2) + dsp->vmovescreen;
	if (dsp->sp_drawy[0] < 0)
		dsp->sp_drawy[0] = 0;
	dsp->sp_drawy[1] = (dsp->sp_height / 2)
		+ (WIN_HEIGHT / 2) + dsp->vmovescreen;
	if (dsp->sp_drawy[1] >= WIN_HEIGHT)
		dsp->sp_drawy[1] = WIN_HEIGHT - 1;
	dsp->sp_width = abs((int)(WIN_HEIGHT / (dsp->transform[0])))
		/ sprites->sp_wdiv;
	dsp->sp_drawx[0] = -dsp->sp_width / 2 + dsp->sp_screen[1];
	if (dsp->sp_drawx[0] < 0)
		dsp->sp_drawx[0] = 0;
	dsp->sp_drawx[1] = dsp->sp_width / 2 + dsp->sp_screen[1];
	if (dsp->sp_drawx[1] >= WIN_WIDTH)
		dsp->sp_drawx[1] = WIN_WIDTH - 1;
}

void	draw_sprites_setup(t_data *data, t_sprites *sprites,
	double zbuff[WIN_WIDTH])
{
	const t_play	pl = data->player;
	t_dsprites		dsp;

	if (sprites->sp_k_or_g == 'K')
	{
		sprites->sp_s_img = sprites->sp_k_s_img[(data->nloop - 1) / 10];
		sprites->sp_hpos = (64.0
				* (sprites->sp_hdiv / 2) + 64.0 - (data->nloop));
	}
	else
		sprites->sp_s_img = sprites->sp_g_s_img[(data->nloop - 1) / 4];
	dsp.sp_pos[1] = sprites->sp_pos[1] - pl.pos[1];
	dsp.sp_pos[0] = sprites->sp_pos[0] - pl.pos[0];
	dsp.invdet = 1.0 / (pl.fov[1] * pl.dir[0] - pl.dir[1] * pl.fov[0]);
	dsp.transform[1] = dsp.invdet
		* (pl.dir[0] * dsp.sp_pos[1] - pl.dir[1] * dsp.sp_pos[0]);
	dsp.transform[0] = dsp.invdet
		* (-pl.fov[0] * dsp.sp_pos[1] + pl.fov[1] * dsp.sp_pos[0]);
	dsp.sp_screen[1] = (int)((WIN_WIDTH / 2)
			* (1 + dsp.transform[1] / dsp.transform[0]));
	dsp.vmovescreen = (int)(sprites->sp_hpos / dsp.transform[0]);
	dsp.sp_height = abs((int)(WIN_HEIGHT / (dsp.transform[0])))
		/ sprites->sp_hdiv;
	draw_sprites_setup2(&dsp, sprites);
	draw_sprites(data, &dsp, sprites, zbuff);
}
