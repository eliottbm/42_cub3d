/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs_inits_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:14:44 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/18 14:22:51 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	imgs_dimcheck(void *tex, void *tex2, int *dim, int *dim2)
{
	if (!tex)
		return (1);
	if (dim[0] > WIN_HEIGHT || dim[1] > WIN_WIDTH)
		return (1);
	if (tex2 && dim2[0] != -1 && dim2[1] != -1
		&& (dim[0] != dim2[0] || dim[1] != dim2[1]))
		return (1);
	return (0);
}

static int	imgs_check2(t_tex tex, t_menu menu)
{
	if ((imgs_dimcheck(tex.arrow, tex.arrow_h,
				(int *)menu.a_dim, (int *)menu.ah_dim))
		|| (imgs_dimcheck(tex.arrow_h, tex.arrow,
				(int *)menu.ah_dim, (int *)menu.a_dim))
		|| (imgs_dimcheck(tex.quit, tex.quit_h,
				(int *)menu.q_dim, (int *)menu.qh_dim))
		|| (imgs_dimcheck(tex.quit_h, tex.quit,
				(int *)menu.qh_dim, (int *)menu.q_dim)))
		return (1);
	return (0);
}

static int	imgs_check(t_data data)
{
	const t_tex		tex = data.tex;
	const t_menu	menu = data.menu;

	if ((!tex.menubg || !tex.mm_o || !tex.mm_sm || !tex.mm_sp
			|| !tex.key[0] || !tex.heart || !tex.selmaps || !tex.dmgbg
			|| !tex.win || !tex.loose || !tex.key[1] || !tex.key[2]
			|| !tex.key[3] || (menu.dmg_dim[0] < WIN_HEIGHT
				|| menu.dmg_dim[1] < WIN_WIDTH)
			|| (menu.bg_dim[0] < WIN_HEIGHT || menu.bg_dim[1] < WIN_WIDTH))
		|| (imgs_dimcheck(tex.resume, tex.resume_h,
				(int *)menu.r_dim, (int *)menu.rh_dim))
		|| (imgs_dimcheck(tex.resume_h, tex.resume,
				(int *)menu.rh_dim, (int *)menu.r_dim))
		|| (imgs_dimcheck(tex.main, tex.main_h,
				(int *)menu.m_dim, (int *)menu.mh_dim))
		|| (imgs_dimcheck(tex.main_h, tex.main,
				(int *)menu.mh_dim, (int *)menu.m_dim))
		|| (imgs_dimcheck(tex.play, tex.play_h,
				(int *)menu.p_dim, (int *)menu.ph_dim))
		|| (imgs_dimcheck(tex.play_h, tex.play,
				(int *)menu.ph_dim, (int *)menu.p_dim))
		|| imgs_check2(tex, menu))
		return (1);
	return (0);
}

int	win_init(t_data *data)
{
	int	tmp;

	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win)
		return (1);
	imgs_init(data, "textures/gengar/menus/background.xpm", 0);
	imgs_init(data, "textures/gengar/menus/resume.xpm", 1);
	imgs_init(data, "textures/gengar/menus/resume_h.xpm", 2);
	imgs_init(data, "textures/gengar/menus/main.xpm", 3);
	imgs_init(data, "textures/gengar/menus/main_h.xpm", 4);
	imgs_init(data, "textures/gengar/menus/play.xpm", 5);
	imgs_init(data, "textures/gengar/menus/play_h.xpm", 6);
	imgs_init(data, "textures/gengar/menus/quit.xpm", 7);
	imgs_init(data, "textures/gengar/menus/quit_h.xpm", 8);
	imgs_init(data, "textures/gengar/menus/choosemap.xpm", 9);
	imgs_init(data, "textures/gengar/menus/arrow.xpm", 10);
	imgs_init_bis(data);
	if (imgs_check(*data) || opps_sprites_init(data))
		return (1);
	imgpos_init(data);
	data->draw.s_world = mlx_get_data_addr(data->draw.i_world, &tmp,
			&data->draw.worldsize, &data->draw.worldend);
	data->draw.s_arrow = mlx_get_data_addr(data->tex.arrow, &tmp,
			&data->draw.arrowsize, &tmp);
	return (0);
}

void	d_anim_init(t_data *data)
{
	if (data->tex.doors)
		data->d_anim.da_img = data->tex.doors->img;
	else
		data->d_anim.da_img = NULL;
	data->d_anim.da_check = 0;
	data->d_anim.da_isdone = 0;
	data->d_anim.da_frame = 1;
	data->d_anim.da_doorpos[0] = ((data->d_anim.da_doorpos[1]) = -1);
	data->d_anim.da_isrun = 0;
}
