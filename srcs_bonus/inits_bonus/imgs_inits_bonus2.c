/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs_inits_bonus2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:15:33 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/18 14:27:50 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	imgs_inits3(t_data *data, char *path, int ntex)
{
	int	tmp;

	if (ntex == 12)
		data->tex.mm_o = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
	else if (ntex == 13)
		data->tex.mm_sm = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
	else if (ntex == 14)
		data->tex.mm_sp = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
	else if (ntex == 15)
		data->tex.heart = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
	else if (ntex == 16)
		data->tex.key[0] = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
	else if (ntex == 17)
		data->tex.win = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.w_dim[1], &data->menu.w_dim[0]);
	else if (ntex == 18)
		data->tex.loose = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.l_dim[1], &data->menu.l_dim[0]);
	else if (ntex == 19)
		data->tex.key[1] = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
	else if (ntex == 20)
		data->tex.key[2] = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
	else if (ntex == 21)
		data->tex.key[3] = mlx_xpm_file_to_image(data->mlx, path, &tmp, &tmp);
}

static void	imgpos_init2(int (*pos)[2], int *dim, int *dim2, int updown)
{
	if (updown)
		(*pos)[0] = (WIN_HEIGHT / 2) - dim[0] - ((dim[0] + dim2[0]) / 3);
	else
		(*pos)[0] = (WIN_HEIGHT / 2) + ((dim[0] + dim2[0]) / 3);
	(*pos)[1] = (WIN_WIDTH / 2) - (dim[1] / 2);
}

void	imgpos_init(t_data *data)
{
	t_menu	*menu;

	menu = &data->menu;
	menu->sm_margin = WIN_HEIGHT / 14;
	menu->mp_dim[0] = WIN_HEIGHT / 4;
	menu->mp_dim[1] = WIN_WIDTH / 4;
	menu->mapspos[0][0] = ((WIN_HEIGHT + menu->sm_margin + menu->sm_dim[0]) / 2)
		- (menu->mp_dim[0] + 60 + menu->sm_margin / 4);
	menu->mapspos[1][0] = ((menu->mapspos[2][0]) = menu->mapspos[0][0]);
	menu->mapspos[3][0] = (menu->mapspos[0][0]
			+ (menu->mp_dim[0] + 60 + menu->sm_margin / 2));
	menu->mapspos[4][0] = ((menu->mapspos[5][0]) = menu->mapspos[3][0]);
	menu->mapspos[0][1] = ((WIN_WIDTH + (menu->sm_margin * 2)) / 3)
		- (menu->mp_dim[1] + 40 + menu->sm_margin / 2);
	menu->mapspos[3][1] = menu->mapspos[0][1];
	menu->mapspos[1][1] = ((WIN_WIDTH + (menu->sm_margin * 2)) / 3);
	menu->mapspos[4][1] = menu->mapspos[1][1];
	menu->mapspos[2][1] = ((WIN_WIDTH + (menu->sm_margin * 2)) / 3)
		+ (menu->mp_dim[1] + 40 + menu->sm_margin / 2);
	menu->mapspos[5][1] = menu->mapspos[2][1];
	imgpos_init2(&(menu->r_pos), menu->r_dim, menu->m_dim, 1);
	imgpos_init2(&(menu->m_pos), menu->m_dim, menu->r_dim, 0);
	imgpos_init2(&(menu->p_pos), menu->p_dim, menu->q_dim, 1);
	imgpos_init2(&(menu->q_pos), menu->q_dim, menu->p_dim, 0);
}

static void	imgs_init2(t_data *data, char *path, int ntex)
{
	if (ntex == 7)
		data->tex.quit = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.q_dim[1], &data->menu.q_dim[0]);
	else if (ntex == 8)
		data->tex.quit_h = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.qh_dim[1], &data->menu.qh_dim[0]);
	else if (ntex == 9)
		data->tex.selmaps = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.sm_dim[1], &data->menu.sm_dim[0]);
	else if (ntex == 10)
		data->tex.arrow = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.a_dim[1], &data->menu.a_dim[0]);
	else if (ntex == 11)
		data->tex.arrow_h = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.ah_dim[1], &data->menu.ah_dim[0]);
	else if (ntex == 22)
		data->tex.dmgbg = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.dmg_dim[1], &data->menu.dmg_dim[0]);
	else
		imgs_inits3(data, path, ntex);
}

void	imgs_init(t_data *data, char *path, int ntex)
{
	if (ntex == 0)
		data->tex.menubg = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.bg_dim[1], &data->menu.bg_dim[0]);
	else if (ntex == 1)
		data->tex.resume = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.r_dim[1], &data->menu.r_dim[0]);
	else if (ntex == 2)
		data->tex.resume_h = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.rh_dim[1], &data->menu.rh_dim[0]);
	else if (ntex == 3)
		data->tex.main = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.m_dim[1], &data->menu.m_dim[0]);
	else if (ntex == 4)
		data->tex.main_h = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.mh_dim[1], &data->menu.mh_dim[0]);
	else if (ntex == 5)
		data->tex.play = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.p_dim[1], &data->menu.p_dim[0]);
	else if (ntex == 6)
		data->tex.play_h = mlx_xpm_file_to_image(data->mlx, path,
				&data->menu.ph_dim[1], &data->menu.ph_dim[0]);
	else
		imgs_init2(data, path, ntex);
}
