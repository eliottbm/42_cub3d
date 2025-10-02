/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_inits_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:31:02 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/20 15:17:49 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	sl2_init(t_l2 *imgl2)
{
	imgl2->s_l2 = NULL;
	imgl2->l2_size = 0;
	imgl2->l2_bits = 0;
	imgl2->l2_scale[1] = 0.0;
	imgl2->l2_scale[0] = 0.0;
	imgl2->l2_pos[1] = 0;
	imgl2->l2_pos[0] = 0;
	imgl2->l2_tex[1] = 0;
	imgl2->l2_tex[0] = 0;
	imgl2->l2_dim[1] = 0;
	imgl2->l2_dim[0] = 0;
}

static void	pause_init(t_menu *menu)
{
	menu->sm_margin = -1;
	menu->w_dim[0] = ((menu->w_dim[1]) = -1);
	menu->l_dim[0] = ((menu->l_dim[1]) = -1);
	menu->mp_dim[0] = ((menu->mp_dim[1]) = -1);
	menu->bg_dim[0] = ((menu->bg_dim[1]) = -1);
	menu->dmg_dim[0] = ((menu->dmg_dim[1]) = -1);
	menu->r_dim[0] = ((menu->r_dim[1]) = -1);
	menu->m_dim[0] = ((menu->m_dim[1]) = -1);
	menu->p_dim[0] = ((menu->p_dim[1]) = -1);
	menu->q_dim[0] = ((menu->q_dim[1]) = -1);
	menu->a_dim[0] = ((menu->a_dim[1]) = -1);
	menu->rh_dim[0] = ((menu->rh_dim[1]) = -1);
	menu->mh_dim[0] = ((menu->mh_dim[1]) = -1);
	menu->ph_dim[0] = ((menu->ph_dim[1]) = -1);
	menu->qh_dim[0] = ((menu->qh_dim[1]) = -1);
	menu->ah_dim[0] = ((menu->ah_dim[1]) = -1);
	menu->sm_dim[0] = ((menu->sm_dim[1]) = -1);
}

static int	menutex_init(t_data *data)
{
	pause_init(&data->menu);
	data->tex.win = NULL;
	data->tex.loose = NULL;
	data->tex.heart = NULL;
	data->tex.key[0] = NULL;
	data->tex.geng[0] = NULL;
	data->tex.menubg = NULL;
	data->tex.dmgbg = NULL;
	data->tex.resume = NULL;
	data->tex.resume_h = NULL;
	data->tex.main = NULL;
	data->tex.main_h = NULL;
	data->tex.play = NULL;
	data->tex.play_h = NULL;
	data->tex.quit = NULL;
	data->tex.quit_h = NULL;
	data->tex.selmaps = NULL;
	data->tex.arrow = NULL;
	data->tex.arrow_h = NULL;
	data->tex.mm_o = NULL;
	data->tex.mm_sm = NULL;
	data->tex.mm_sp = NULL;
	return (0);
}

void	data_init(t_data *data)
{
	data->is_end = 0;
	data->is_dmg = -1;
	data->nb_opps = 0;
	data->nloop = 0;
	data->loopback = 0;
	data->is_key = ((data->is_opp) = 0);
	data->d_draw.s_check = 0;
	data->d_draw.s_w_dist = -1;
	data->menu.selected = 0;
	data->tex.n_doors = 0;
	data->map = NULL;
	data->gengar = NULL;
	data->tex.exit = NULL;
	data->tex.doors = NULL;
	data->tex.wall = NULL;
	data->tex.wall2 = NULL;
	data->tex.ceil = NULL;
	data->tex.floor = NULL;
	d_anim_init(data);
	sl2_init(&data->imgl2);
}

int	game_init(t_game *game, char *dir)
{
	game->mdir = dir;
	game->nmaps = 0;
	game->maps = NULL;
	game->data.menu.ispaused = 1;
	game->data.win = NULL;
	data_init(&game->data);
	menutex_init(&game->data);
	game->data.mlx = mlx_init();
	if (!game->data.mlx)
		return (1);
	game->data.draw.i_world = mlx_new_image(
			game->data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->data.draw.i_world)
		return (1);
	if (win_init(&game->data))
		return (1);
	return (0);
}
