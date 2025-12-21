/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:04:03 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/20 16:55:27 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_STRUCT_H
# define CUB3D_BONUS_STRUCT_H

typedef struct l_doors
{
	size_t			n;
	void			*img;
	struct l_doors	*next;
}					t_doors;

typedef struct l_maps
{
	char			*name;
	char			*path;
	void			*preview;
	struct l_maps	*next;
}					t_maps;

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
}			t_ray;

typedef struct s_mmtex
{
	int		k;
	int		i;
	int		y;
	int		x;
	int		xp;
	int		yp;
	int		tmp;
	int		szl1;
	int		szl2;
	int		c;
	char	*s_sha;
	char	*s_tex;
}			t_mmtex;

typedef struct s_tex
{
	int		n_doors;
	t_doors	*doors;
	void	*exit;
	void	*key[4];
	void	*heart;
	void	*wall2;
	void	*wall;
	void	*ceil;
	void	*floor;
	void	*menubg;
	void	*dmgbg;
	void	*resume;
	void	*resume_h;
	void	*win;
	void	*loose;
	void	*main;
	void	*main_h;
	void	*play;
	void	*play_h;
	void	*quit;
	void	*quit_h;
	void	*selmaps;
	void	*arrow;
	void	*arrow_h;
	void	*mm_o;
	void	*mm_sm;
	void	*mm_sp;
	void	*geng[20];
}			t_tex;

typedef struct s_draw
{
	int		d_start;
	int		d_end;
	int		d_dist;
	char	*s_arrow;
	int		arrowsize;
	int		height;
	int		start;
	void	*i_world;
	char	*s_world;
	int		worldsize;
	int		worldend;
	char	*s_wall;
	double	w_texpos;
	double	w_step;
	int		w_tex[2];
	char	*s_ceil;
	char	*s_floor;
	float	cf_rdirx[2];
	float	cf_rdiry[2];
	int		cf_p;
	float	cf_posz;
	float	cf_dist;
	float	cf_step[2];
	float	cf_floor[2];
	int		cf_cell[2];
	int		cf_texpos[2];
}			t_draw;

typedef struct s_menu
{
	int		ispaused;
	int		selected;
	int		sm_margin;
	int		mp_dim[2];
	int		w_dim[2];
	int		l_dim[2];
	int		mapspos[6][2];
	int		bg_dim[2];
	int		dmg_dim[2];
	int		r_dim[2];
	int		rh_dim[2];
	int		m_dim[2];
	int		mh_dim[2];
	int		p_dim[2];
	int		ph_dim[2];
	int		q_dim[2];
	int		qh_dim[2];
	int		sm_dim[2];
	int		a_dim[2];
	int		ah_dim[2];
	int		r_pos[2];
	int		m_pos[2];
	int		p_pos[2];
	int		q_pos[2];
}			t_menu;

typedef struct s_opps
{
	double			dist;
	double			pos[2];
	int				seen;
	int				sprite;
	int				last_m;
	struct s_opps	*prev;
	struct s_opps	*next;
}					t_opps;

typedef struct s_l2
{
	char	*s_l2;
	int		l2_size;
	int		l2_bits;
	double	l2_scale[2];
	int		l2_pos[2];
	int		l2_tex[2];
	int		l2_dim[2];
}			t_l2;

typedef struct s_play
{
	double	pos[2];
	double	dir[2];
	double	fov[2];
	double	m_speed;
	double	m_rota;
	int		hp;
	int		keys;
}			t_play;

typedef struct s_save
{
	int		s_check;
	double	s_w_dist;
	double	s_w_hit;
	int		s_height;
	int		s_start;
	double	s_w_texpos;
	double	s_w_step;
	int		s_w_tex[2];
	char	*s_s_img;
}			t_save;

typedef struct s_danim
{
	double	da_w_dist;
	int		da_isrun;
	int		da_doorpos[2];
	int		da_check;
	void	*da_img;
	int		da_frame;
	int		da_isdone;
}			t_danim;

typedef struct s_dsprites
{
	double	sp_pos[2];
	double	invdet;
	double	transform[2];
	int		sp_screen[2];
	int		vmovescreen;
	int		sp_height;
	int		sp_drawx[2];
	int		sp_drawy[2];
	int		sp_width;
	int		sp_texpos[2];
	int		sp_d;
	int		sp_dist;
}			t_dsprites;

typedef struct s_sprites
{
	int		sp_isview;
	int		sp_wdiv;
	int		sp_hdiv;
	double	sp_hpos;
	char	sp_k_or_g;
	double	sp_pos[2];
	double	sp_dist;
	char	*sp_s_img;
	char	*sp_k_s_img[4];
	char	*sp_g_s_img[20];
}			t_sprites;

typedef struct s_data
{
	t_tex		tex;
	t_play		player;
	t_ray		ray;
	t_draw		draw;
	t_menu		menu;
	t_opps		*gengar;
	t_sprites	sprites[OPPS_NBR + 1];
	t_l2		imgl2;
	t_save		d_draw;
	t_danim		d_anim;
	int			nb_opps;
	int			is_key;
	int			is_opp;
	int			is_end;
	int			is_dmg;
	char		**map;
	int			h_map;
	void		*mlx;
	void		*win;
	int			nloop;
	int			loopback;
}				t_data;

typedef struct s_game
{
	t_data	data;
	t_maps	*maps;
	int		nmaps;
	char	*mdir;
}			t_game;

#endif