/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_previews_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:46:54 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/22 16:14:34 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	draw_previews2(t_draw *draw, int bits, int border, int hover)
{
	int	color;

	if (border && !hover)
		color = ((220 * 65536) + (220 * 256) + 220);
	else if (!border && !hover)
		color = ((255 * 65536) + (255 * 256) + 255);
	else if (border && hover)
		color = ((165 * 65536) + (67 * 256) + 68);
	else if (!border && hover)
		color = ((214 * 65536) + (93 * 256) + 84);
	if (draw->worldend)
	{
		draw->s_world[bits + 0] = (color >> 24);
		draw->s_world[bits + 1] = (color >> 16) & 0xFF;
		draw->s_world[bits + 2] = (color >> 8) & 0xFF;
		draw->s_world[bits + 3] = (color) & 0xFF;
	}
	else
	{
		draw->s_world[bits + 0] = (color) & 0xFF;
		draw->s_world[bits + 1] = (color >> 8) & 0xFF;
		draw->s_world[bits + 2] = (color >> 16) & 0xFF;
		draw->s_world[bits + 3] = (color >> 24);
	}
}

static void	draw_texts(t_game *game, int i, char *name)
{
	int	x;
	int	y;

	if (!name)
	{
		x = game->data.menu.mapspos[i][1]
			+ (game->data.menu.mp_dim[1] + 40) / 2.55;
		y = game->data.menu.mapspos[i][0]
			+ (game->data.menu.mp_dim[0] + 60) / 2;
		mlx_string_put(game->data.mlx, game->data.win,
			x, y, 0, "no map to load");
	}
	else
	{
		x = game->data.menu.mapspos[i][1] + 20;
		y = game->data.menu.mapspos[i][0]
			+ (game->data.menu.mp_dim[0] + 60) - 17;
		mlx_string_put(game->data.mlx, game->data.win,
			x, y, 0, name);
	}
}

void	draw_texts_setup(t_game *game, int i)
{
	t_maps	*maps;
	int		j;

	j = 0;
	maps = game->maps;
	while (maps && j != i)
	{
		maps = maps->next;
		j++;
	}
	if (maps && j == i)
		draw_texts(game, i, maps->name);
	else
		draw_texts(game, i, NULL);
}

static void	draw_previews(t_game *game, int i)
{
	t_maps	*maps;
	int		j;
	int		tmp;

	if (game->nmaps < i + 1)
		return ;
	j = 0;
	maps = game->maps;
	while (maps && j < i)
	{
		maps = maps->next;
		j++;
	}
	game->data.imgl2.l2_dim[0] = game->data.menu.mp_dim[0];
	game->data.imgl2.l2_dim[1] = game->data.menu.mp_dim[1];
	game->data.imgl2.l2_pos[0] = game->data.menu.mapspos[i][0] + 20;
	game->data.imgl2.l2_pos[1] = game->data.menu.mapspos[i][1] + 20;
	game->data.imgl2.s_l2 = mlx_get_data_addr(
			maps->preview, &tmp, &game->data.imgl2.l2_size, &tmp);
	l2draw(&game->data, 0);
	sl2_init(&game->data.imgl2);
}

void	draw_previews_setup(t_game *game, int i, int hover)
{
	int				x;
	int				y;
	int				bits;
	const t_menu	menu = game->data.menu;

	x = menu.mapspos[i][1];
	while (x < menu.mapspos[i][1] + menu.mp_dim[1] + 40)
	{
		y = menu.mapspos[i][0];
		while (y < menu.mapspos[i][0] + menu.mp_dim[0] + 60)
		{
			bits = (y * game->data.draw.worldsize) + (x * 4);
			if (x < menu.mapspos[i][1] + 3 || x > menu.mapspos[i][1]
				+ menu.mp_dim[1] + 36 || y < menu.mapspos[i][0] + 3
				|| y > menu.mapspos[i][0] + menu.mp_dim[0] + 56)
				draw_previews2(&game->data.draw, bits, 1, hover);
			else
				draw_previews2(&game->data.draw, bits, 0, hover);
			y++;
		}
		x++;
	}
	draw_previews(game, i);
	mlx_put_image_to_window(game->data.mlx, game->data.win,
		game->data.draw.i_world, 0, 0);
}
