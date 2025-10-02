/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:16:45 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/20 15:42:53 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	free_tex2(t_data data, t_tex tex)
{
	if (tex.main)
		mlx_destroy_image(data.mlx, tex.main);
	if (tex.main_h)
		mlx_destroy_image(data.mlx, tex.main_h);
	if (tex.selmaps)
		mlx_destroy_image(data.mlx, tex.selmaps);
	if (tex.play)
		mlx_destroy_image(data.mlx, tex.play);
	if (tex.play_h)
		mlx_destroy_image(data.mlx, tex.play_h);
	if (tex.quit)
		mlx_destroy_image(data.mlx, tex.quit);
	if (tex.quit_h)
		mlx_destroy_image(data.mlx, tex.quit_h);
	if (tex.arrow)
		mlx_destroy_image(data.mlx, tex.arrow);
	if (tex.arrow_h)
		mlx_destroy_image(data.mlx, tex.arrow_h);
	if (tex.mm_o)
		mlx_destroy_image(data.mlx, tex.mm_o);
	if (tex.mm_sm)
		mlx_destroy_image(data.mlx, tex.mm_sm);
	if (tex.mm_sp)
		mlx_destroy_image(data.mlx, tex.mm_sp);
}

static void	free_tex(t_data data, t_tex tex)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (tex.key[i])
			mlx_destroy_image(data.mlx, tex.key[i]);
	if (data.draw.i_world)
		mlx_destroy_image(data.mlx, data.draw.i_world);
	if (tex.menubg)
		mlx_destroy_image(data.mlx, tex.menubg);
	if (tex.dmgbg)
		mlx_destroy_image(data.mlx, tex.dmgbg);
	if (tex.resume)
		mlx_destroy_image(data.mlx, tex.resume);
	if (tex.resume_h)
		mlx_destroy_image(data.mlx, tex.resume_h);
	if (tex.heart)
		mlx_destroy_image(data.mlx, tex.heart);
	if (tex.win)
		mlx_destroy_image(data.mlx, tex.win);
	if (tex.loose)
		mlx_destroy_image(data.mlx, tex.loose);
	if (tex.geng[0])
		destroy_opps_sprites(&data);
	free_tex2(data, tex);
}

static void	free_texdata(t_data data)
{
	t_tex	tex;

	tex = data.tex;
	if (tex.wall)
		mlx_destroy_image(data.mlx, tex.wall);
	if (tex.wall2)
		mlx_destroy_image(data.mlx, tex.wall2);
	if (tex.ceil)
		mlx_destroy_image(data.mlx, tex.ceil);
	if (tex.floor)
		mlx_destroy_image(data.mlx, tex.floor);
	if (tex.exit)
		mlx_destroy_image(data.mlx, tex.exit);
	if (tex.doors)
		d_lstclear(data, tex.doors);
}

void	free_data(t_data data)
{
	free_texdata(data);
	free_gengar(&data);
	if (data.map)
		ft_free_split(data.map);
}

void	free_game(t_game game)
{
	if (game.maps)
		m_lstclear(game.data, &game.maps);
	free_data(game.data);
	free_tex(game.data, game.data.tex);
	if (game.data.mlx && game.data.win)
		mlx_destroy_window(game.data.mlx, game.data.win);
	if (game.data.mlx)
	{
		mlx_destroy_display(game.data.mlx);
		free(game.data.mlx);
	}
}
