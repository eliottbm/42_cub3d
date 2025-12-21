/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs_inits_bonus3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/18 14:17:33 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	imgs_init_bis(t_data *data)
{
	imgs_init(data, "textures/gengar/menus/arrow_h.xpm", 11);
	imgs_init(data, "textures/gengar/mmap/map_overlay.xpm", 12);
	imgs_init(data, "textures/gengar/mmap/map_shape.xpm", 13);
	imgs_init(data, "textures/gengar/mmap/player_shape.xpm", 14);
	imgs_init(data, "textures/gengar/assets/heart.xpm", 15);
	imgs_init(data, "textures/gengar/assets/key.xpm", 16);
	imgs_init(data, "textures/gengar/menus/win.xpm", 17);
	imgs_init(data, "textures/gengar/menus/loose.xpm", 18);
	imgs_init(data, "textures/gengar/assets/key_1.xpm", 19);
	imgs_init(data, "textures/gengar/assets/key_2.xpm", 20);
	imgs_init(data, "textures/gengar/assets/key_3.xpm", 21);
	imgs_init(data, "textures/gengar/menus/dmg_effect.xpm", 22);
}

void	load_reset(t_game *game)
{
	if (game->maps)
		m_lstclear(game->data, &game->maps);
	game->maps = NULL;
	game->nmaps = 0;
	free_data(game->data);
	data_init(&game->data);
}
