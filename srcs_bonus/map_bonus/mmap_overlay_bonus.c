/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_overlay_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:12:41 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/30 17:23:28 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	_mmap_draw_overlay(t_data *data, t_mmtex *v)
{
	int		ws;
	char	*sw;
	int		bits[3];

	ws = data->draw.worldsize;
	sw = data->draw.s_world;
	bits[0] = ((v->yp - (((v->x))) + v->i) * ws)
		+ ((v->xp + ((v->y)) + v->k) * 4);
	bits[1] = ((((v->x)) + v->i) * v->szl2)
		+ (((v->y) + v->k) * 4);
	bits[2] = ((v->x + v->i) * v->szl2)
		+ ((v->y + v->k) * 4);
	if (v->s_sha[bits[2] + 0] != (unsigned char)0
		&& v->s_sha[bits[2] + 1] != (unsigned char)0
		&& v->s_sha[bits[2] + 2] != (unsigned char)0)
	{
		sw[bits[0] + 0] = v->s_sha[bits[1] + 0];
		sw[bits[0] + 1] = v->s_sha[bits[1] + 1];
		sw[bits[0] + 2] = v->s_sha[bits[1] + 2];
		sw[bits[0] + 3] = v->s_sha[bits[1] + 3];
	}
}

int	_draw_overlay(t_data *data)
{
	t_mmtex	v;
	void	*shape;

	shape = data->tex.mm_o;
	v.k = -1;
	v.x = 0;
	v.y = 0;
	v.yp = (WIN_HEIGHT - (WIN_HEIGHT / 3.2));
	v.xp = (WIN_WIDTH - (WIN_WIDTH / 5.1));
	v.szl2 = 242 * 4;
	v.c = 1;
	v.s_sha = mlx_get_data_addr(shape, &v.tmp, &v.szl2, &v.tmp);
	if (!v.s_sha)
		return (1);
	while (++v.k < 242)
	{
		v.i = -1;
		while (++v.i < 218)
			_mmap_draw_overlay(data, &v);
	}
	return (0);
}
