/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_draw2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:44:04 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/02 12:53:51 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static inline void	_mmap_draw_case(t_data *data, t_mmtex *v)
{
	int		ws;
	char	*sw;
	int		bits[3];

	ws = data->draw.worldsize;
	sw = data->draw.s_world;
	bits[0] = ((v->yp - (((v->x) * 32)) + v->i) * ws)
		+ ((v->xp + ((v->y * 32)) + v->k) * 4);
	bits[1] = ((((v->x) * 32) + v->i) * v->szl2)
		+ (((v->y * 32) + v->k) * 4);
	bits[2] = ((v->i) * v->szl1) + ((v->c * v->k) * 4);
	if (v->s_sha[bits[1] + 0] != (unsigned char)0
		&& v->s_sha[bits[1] + 1] != (unsigned char)0
		&& v->s_sha[bits[1] + 2] != (unsigned char)0)
	{
		sw[bits[0] + 0] = v->s_tex[bits[2] + 0];
		sw[bits[0] + 1] = v->s_tex[bits[2] + 1];
		sw[bits[0] + 2] = v->s_tex[bits[2] + 2];
		sw[bits[0] + 3] = v->s_tex[bits[2] + 3];
	}
}

static inline void	_mmap_draw_key(t_data *data, t_mmtex *v)
{
	int		ws;
	char	*sw;
	int		bits[3];

	ws = data->draw.worldsize;
	sw = data->draw.s_world;
	bits[0] = ((v->yp - (((v->x) * 32)) + v->i) * ws)
		+ ((v->xp + ((v->y * 32)) + v->k) * 4);
	bits[1] = ((((v->x) * 32) + v->i) * v->szl2)
		+ (((v->y * 32) + v->k) * 4);
	bits[2] = ((v->c * v->i) * v->szl1) + ((v->c * v->k) * 4);
	if (v->s_sha[bits[1] + 0] != (unsigned char)0
		&& v->s_sha[bits[1] + 1] != (unsigned char)0
		&& v->s_sha[bits[1] + 2] != (unsigned char)0
		&& v->s_tex[bits[2] + 0] != (unsigned char)0
		&& v->s_tex[bits[2] + 1] != (unsigned char)0
		&& v->s_tex[bits[2] + 2] != (unsigned char)0)
	{
		sw[bits[0] + 0] = v->s_tex[bits[2] + 0];
		sw[bits[0] + 1] = v->s_tex[bits[2] + 1];
		sw[bits[0] + 2] = v->s_tex[bits[2] + 2];
		sw[bits[0] + 3] = v->s_tex[bits[2] + 3];
	}
}

static inline void	init_draw_pixel(t_mmtex *v, int x, int y)
{
	v->k = -1;
	v->x = x;
	v->y = y;
	v->yp = WIN_HEIGHT - (WIN_HEIGHT / PX_MMAP);
	v->xp = WIN_WIDTH - (WIN_WIDTH / PY_MMAP);
	v->szl1 = TEX_SIZE * 4;
	v->szl2 = 160 * 4;
	v->c = TEX_SIZE / (TEX_SIZE / 2);
}

int	_mmap_draw_pixel(t_data *data, int (x)[2], void *text, int flag)
{
	t_mmtex	v;
	void	*shape;

	shape = data->tex.mm_sm;
	init_draw_pixel(&v, x[0], x[1]);
	v.s_sha = mlx_get_data_addr(shape, &v.tmp, &v.szl2, &v.tmp);
	v.s_tex = mlx_get_data_addr(text, &v.tmp, &v.szl1, &v.tmp);
	if (!v.s_sha || !v.s_tex)
		return (1);
	while (++v.k < 32)
	{
		v.i = -1;
		while (++v.i < 32)
		{
			if (flag)
				_mmap_draw_key(data, &v);
			else
				_mmap_draw_case(data, &v);
		}
	}
	return (0);
}
