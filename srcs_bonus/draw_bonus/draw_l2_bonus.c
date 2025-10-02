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

static inline void	l2draw2(t_data *data, int bits, char *s_src, int srcbits)
{
	data->draw.s_world[bits + 0] = s_src[srcbits + 0];
	data->draw.s_world[bits + 1] = s_src[srcbits + 1];
	data->draw.s_world[bits + 2] = s_src[srcbits + 2];
	data->draw.s_world[bits + 3] = s_src[srcbits + 3];
}

void	l2draw(t_data *data, int ign)
{
	int		x;
	int		y;
	int		bits;
	t_l2	*imgl2;

	imgl2 = &data->imgl2;
	x = imgl2->l2_pos[1];
	while (x < imgl2->l2_pos[1] + imgl2->l2_dim[1])
	{
		y = imgl2->l2_pos[0];
		while (y < imgl2->l2_pos[0] + imgl2->l2_dim[0])
		{
			imgl2->l2_bits = ((y - imgl2->l2_pos[0]) * imgl2->l2_size)
				+ ((x - imgl2->l2_pos[1]) * 4);
			bits = ((y * data->draw.worldsize) + (x * 4));
			if (ign && imgl2->s_l2[imgl2->l2_bits] == 0
				&& imgl2->s_l2[imgl2->l2_bits + 1] == 0
				&& imgl2->s_l2[imgl2->l2_bits + 2] == 0)
				l2draw2(data, bits, data->draw.s_world, bits);
			else
				l2draw2(data, bits, imgl2->s_l2, imgl2->l2_bits);
			y++;
		}
		x++;
	}
}

static void	tookdmg_setup(t_data *data)
{
	int	tmp;

	data->imgl2.l2_pos[1] = WIN_WIDTH;
	data->imgl2.l2_pos[0] = WIN_HEIGHT;
	data->imgl2.s_l2 = mlx_get_data_addr(
			data->tex.dmgbg, &tmp, &data->imgl2.l2_size, &tmp);
	data->imgl2.l2_dim[1] = data->menu.bg_dim[1];
	data->imgl2.l2_dim[0] = data->menu.bg_dim[0];
	data->imgl2.l2_scale[1] = (
			(double)data->imgl2.l2_pos[1] / (double)data->imgl2.l2_dim[1]);
	data->imgl2.l2_scale[0] = (
			(double)data->imgl2.l2_pos[0] / (double)data->imgl2.l2_dim[0]);
	draw_resize(data, data->draw.s_world, data->draw.worldsize, 2);
}

static void	sort_sprites(t_data *data)
{
	register int	i;
	t_sprites		tmp;

	i = 0;
	while (i < OPPS_NBR + 1)
	{
		if (i > 0 && data->sprites[i - 1].sp_dist < data->sprites[i].sp_dist)
		{
			tmp = data->sprites[i - 1];
			data->sprites[i - 1] = data->sprites[i];
			data->sprites[i] = tmp;
		}
		i++;
	}
}

void	handle_sprites(t_data *data, double *zbuff)
{
	register int	i;

	(sort_sprites(data), sort_sprites(data));
	i = 0;
	while (i < OPPS_NBR + 1)
	{
		if (data->sprites[i].sp_isview != 0)
		{
			draw_sprites_setup(data, &data->sprites[i], zbuff);
			data->sprites[i].sp_isview = 0;
			data->sprites[i].sp_dist = -1.0;
		}
		i++;
	}
	if (data->is_dmg > 0)
	{
		tookdmg_setup(data);
		if (data->nloop == data->is_dmg + 3 || data->nloop == data->is_dmg - 3)
			data->is_dmg = -1;
	}
}
