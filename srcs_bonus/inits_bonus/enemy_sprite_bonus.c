/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sprite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:00:57 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/20 15:41:40 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	init_opps_pars(t_data *data)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		data->tex.geng[i] = NULL;
		i++;
	}
}

void	destroy_opps_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		if (data->tex.geng[i])
			mlx_destroy_image(data->mlx, data->tex.geng[i]);
		i++;
	}
}

static int	verif_init(t_data *data)
{
	int	i;

	i = 0;
	while (i <= 19)
	{
		if (!data->tex.geng[i])
			return (1);
		i++;
	}
	return (0);
}

static void	opps_sprites_init2(t_data *data, int *size)
{
	data->tex.geng[9] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g9.xpm", size, size);
	data->tex.geng[10] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g10.xpm", size, size);
	data->tex.geng[11] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g11.xpm", size, size);
	data->tex.geng[12] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g12.xpm", size, size);
	data->tex.geng[13] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g13.xpm", size, size);
	data->tex.geng[14] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g14.xpm", size, size);
	data->tex.geng[15] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g15.xpm", size, size);
	data->tex.geng[16] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g16.xpm", size, size);
	data->tex.geng[17] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g17.xpm", size, size);
	data->tex.geng[18] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g18.xpm", size, size);
	data->tex.geng[19] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g19.xpm", size, size);
}

int	opps_sprites_init(t_data *data)
{
	int	size;

	size = 64;
	init_opps_pars(data);
	data->tex.geng[0] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g0.xpm", &size, &size);
	data->tex.geng[1] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g1.xpm", &size, &size);
	data->tex.geng[2] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g2.xpm", &size, &size);
	data->tex.geng[3] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g3.xpm", &size, &size);
	data->tex.geng[4] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g4.xpm", &size, &size);
	data->tex.geng[5] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g5.xpm", &size, &size);
	data->tex.geng[6] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g6.xpm", &size, &size);
	data->tex.geng[7] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g7.xpm", &size, &size);
	data->tex.geng[8] = mlx_xpm_file_to_image(data->mlx,
			"textures/gengar/opps/g8.xpm", &size, &size);
	opps_sprites_init2(data, &size);
	return (verif_init(data));
}
