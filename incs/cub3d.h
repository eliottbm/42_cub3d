/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:54:51 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/30 15:00:44 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/time.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "../libft/incs/ft_printf.h"
# include "../minilibx-linux/mlx.h"

# define WIN_HEIGHT 720
# define WIN_WIDTH 1480
# define TEX_SIZE 64
# define ROTATE_SPEED 6
# define MOOVE_SPEED 12
# define FOV_DEG 80
# define ESC_KEYCODE 65307
# define RGT_KEYCODE 65363
# define LFT_KEYCODE 65361
# define W_KEYCODE 119
# define S_KEYCODE 115
# define A_KEYCODE 97
# define D_KEYCODE 100
# define M_PI 3.14159265358979323846

typedef enum s_dir
{
	NONE,
	NORTH,
	WEST,
	SOUTH,
	EAST
}	t_dir;

typedef struct s_ray
{
	double	dir[2];
	double	dist[2];
	double	delta[2];
	double	w_dist;
	int		pos[2];
	int		step[2];
	int		hit;
	int		side;
	double	w_hit;
	double	b_time;
	double	e_time;
	double	fps;
	t_dir	tdir;
}			t_ray;

typedef struct s_tex
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	int		f;
	int		c;
}			t_tex;

typedef struct s_draw
{
	int		height;
	int		start;
	int		tex[2];
	double	step;
	double	pos;
	void	*i_world;
	char	*s_world;
	int		worldsize;
	int		worldend;
	char	*s_wall;
	int		wallsize;
}			t_draw;

typedef struct s_play
{
	double	pos[2];
	double	dir[2];
	double	fov[2];
	double	m_speed;
	double	m_rota;
}			t_play;

typedef struct s_data
{
	t_tex	tex;
	t_play	player;
	t_ray	ray;
	t_draw	draw;
	char	**map;
	void	*mlx;
	void	*win;
}			t_data;

void	free_data(t_data data);

int		parsing(t_data *data, char *file);
int		check_ext(char *file, char *ext);
int		set_textures(t_data *data, char *buf);
int		is_wall(char c);
char	*strrmset(char *str, char c);
int		tab_iscolor(char **tab);
int		isline_valid(char *line, int ntex);
int		validmap_checks(char **map, char c, size_t y, size_t x);
int		ismapvalid_chars(char **map);
int		ismapvalid_format(t_data *data);

void	raycast(t_data *data);
void	draw_setup(t_ray ray, t_draw *draw, t_tex tex);
void	draw_world(t_data data, t_draw *draw, int i);

int		end_mlx(t_data *data);
int		listen_inputs(int key, t_data *data);

size_t	get_current_time(void);
void	calc_fps(t_data *data);

void	moov_player_ws(int keycode, t_data *data);
void	moov_player_ad(int keycode, t_data *data);

#endif