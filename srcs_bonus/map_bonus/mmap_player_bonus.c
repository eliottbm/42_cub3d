/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:14:08 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/28 17:53:18 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	_mmap_draw_player(t_data *data, t_mmtex *v, int color)
{
	int		ws;
	char	*sw;
	int		bits[2];

	ws = data->draw.worldsize;
	sw = data->draw.s_world;
	bits[0] = ((v->yp - (((v->x) * 32)) + v->i) * ws)
		+ ((v->xp + ((v->y * 32)) + v->k) * 4);
	bits[1] = ((v->x + v->i) * v->szl2)
		+ ((v->y + v->k) * 4);
	if (v->s_sha[bits[1] + 0] != (unsigned char)0
		&& v->s_sha[bits[1] + 1] != (unsigned char)0
		&& v->s_sha[bits[1] + 2] != (unsigned char)0)
	{
		sw[bits[0] + 0] = (color >> 16) & 0xFF;
		sw[bits[0] + 1] = (color >> 8) & 0xFF;
		sw[bits[0] + 2] = color & 0xFF;
		sw[bits[0] + 3] = (color >> 24) & 0xFF;
	}
}

int	_draw_player(t_data *data)
{
	t_mmtex	v;
	int		color;
	void	*img;

	img = data->tex.mm_sp;
	v.k = -1;
	v.x = 2;
	v.y = 2;
	v.yp = WIN_HEIGHT - (WIN_HEIGHT / PX_MMAP);
	v.xp = WIN_WIDTH - (WIN_WIDTH / PY_MMAP);
	v.szl1 = 16 * 4;
	v.szl2 = 32 * 4;
	v.c = TEX_SIZE / (TEX_SIZE / 2);
	v.s_sha = mlx_get_data_addr(img, &v.tmp, &v.szl2, &v.tmp);
	if (!v.s_sha)
		return (1);
	color = encode_color(P_B, P_G, P_R, 0);
	while (++v.k < 32)
	{
		v.i = -1;
		while (++v.i < 32)
			_mmap_draw_player(data, &v, color);
	}
	return (0);
}
