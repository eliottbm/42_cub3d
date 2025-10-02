/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:54:51 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/20 16:55:11 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <sys/time.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/extensions/Xfixes.h>
# include <X11/keysym.h>
# include <dirent.h>
# include <time.h>

# include "../libft/incs/ft_printf.h"
# include "../minilibx-linux/mlx.h"

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define TEX_SIZE 64
# define DOOR_SPEED 3
# define ROTATE_SPEED 1.1
# define MOOVE_SPEED 3
# define PAUSE_OPACITY 0.3
# define FOV_DEG 80
# define FOG_DIST 4.0
# define ESC_KEYCODE 65307
# define W_KEYCODE 119
# define S_KEYCODE 115
# define A_KEYCODE 97
# define D_KEYCODE 100
# define M_PI 3.14159265358979323846
# define NONE 0
# define PLAY 1
# define QUIT 2
# define RESUME 3
# define MAIN 4
# define P_R 10
# define P_G 70
# define P_B 150
# define M_R 10
# define M_G 70
# define M_B 150
# define MMAP_OPACITY 0.05
# define PX_MMAP 11
# define PY_MMAP 5.6
# define BACK 5
# define MAP1 6
# define MAP2 7
# define MAP3 8
# define MAP4 9
# define MAP5 10
# define MAP6 11
# define OPPS_NBR 1
# define OPPS_AWAY 4
# define O_SPEED 0.18
# define PLAYER_HEALTH 3
# define KEY_AWAY 5
# define EXIT_AWAY 5

# include "./cub3d_bonus_struct.h"

int				game_init(t_game *game, char *dir);
void			data_init(t_data *data);
int				win_init(t_data *data);
int				play_init(t_game *game);
void			sl2_init(t_l2 *imgl2);
void			d_anim_init(t_data *data);
void			imgs_init(t_data *data, char *path, int ntex);
void			imgs_init_bis(t_data *data);
void			imgpos_init(t_data *data);
void			init_opps_pars(t_data *data);
int				opps_sprites_init(t_data *data);
void			free_data(t_data data);
void			free_game(t_game game);
void			destroy_opps_sprites(t_data *data);
void			load_reset(t_game *game);

void			load_reset(t_game *game);
int				read_maps(t_game *game);
int				parsing(t_data *data, char *file);
int				is_texture_set(t_data *data, char *line, int *i);
int				check_ext(char *file, char *ext);
void			*trim_name(char *str);
int				set_textures(t_data *data, char *buf);
int				is_wall(char c);
char			*strrmset(char *str, char c);
int				isline_valid(char *line);
int				validmap_checks(char **map, char c, size_t y, size_t x);
int				ismapvalid_chars(t_data *data, char **map);
int				ismapvalid_format(t_data *data);

t_maps			*m_lstnew(char *name, char *path);
t_maps			*m_lstlast(t_maps *lst);
void			m_lstadd_front(t_maps **lst, t_maps *new);
void			m_lstadd_back(t_maps **lst, t_maps *new);
int				m_lstsize(t_maps *lst);
void			m_nodefree(t_data data, t_maps *map_node);
void			m_lstclear(t_data data, t_maps **lst_maps);

int				handle_doors(t_data *data);
int				is_lookdoor(t_data *data);
t_doors			*d_lstnew(void *img, size_t n);
int				d_lstsize(t_doors *lst);
void			*get_ndoor_img(t_doors *lst, size_t	n);
void			d_lstadd_sort(t_doors **lst, t_doors *new);
void			d_lstclear(t_data data, t_doors *lst_doors);
int				d_lstorder_check(t_doors *doors);

void			raycast(t_data *data, int ispreview);
void			run_dda(t_data *data, t_ray *ray, char **map, int isrun);
void			ray_update(t_ray *ray, t_play player, int x);
void			ray_hit(t_ray *ray, t_play player);
void			ray_step(t_ray *ray, t_play player);

int				end_mlx(t_data *data);
int				listen_clicks(int click, int x, int y, t_game *game);
int				listen_keys(int key, t_data *data);
void			moov_player_ws(int keycode, t_data *data);
void			moov_player_ad(int keycode, t_data *data);
void			rotate_cam(t_data *data, int rotatedir);
int				listen_mouse(int x, int y, t_game *game);
void			mouse_maps(int x, int y, t_game *game, t_menu menu);
int				is_cellav(t_data *data, int x, int y);
void			resume_game(t_data *data);
int				menu_setup(t_data *data, int ispause);
void			opts_setup(t_data *data, int option, int hover);

void			save_draw_infos(t_data data, t_save *s_draw, void *img);
void			draw_floor_setup(t_data *data, int y);
void			handle_sprites(t_data *data, double *zbuff);
void			draw_floor(t_data *data, int y);
void			draw_map_select(t_game *game);
void			draw_texts_setup(t_game *game, int i);
void			draw_previews_setup(t_game *game, int i, int hover);
void			draw_back_arrow(t_data *data, int hover);
void			draw_resize(t_data *data, char *s_img,
					int imgsize, int opacity);
void			draw_sprites_setup(t_data *data,
					t_sprites *sprites, double zbuff[WIN_WIDTH]);
void			draw_walls_setup(char **map, t_ray ray,
					t_draw *draw, t_data *data);
void			draw_walls(t_data *data, int x);
void			draw_static_title(t_data *data, int title);
void			l2draw(t_data *data, int ign);

unsigned char	blend_pixels(
					unsigned char actual_color,
					unsigned char toput_color, double opacity);

size_t			get_current_time(void);
void			calc_fps(t_data *data);
int				encode_color(unsigned char red, unsigned char green,
					unsigned char blue, unsigned char alpha);
int				correct_pos(char **map, int x, int y);
int				minimap(t_data *data);
int				_mmap_draw(t_data *data, char **map);
int				_mmap_draw_pixel(t_data *data,
					int (pos)[2], void *text, int flag);

int				_draw_overlay(t_data *data);
int				_draw_player(t_data *data);
void			_draw_vector_group(t_data *data);
int				_draw_hp(t_data *data);
int				_draw_key(t_data *data);

int				opps_main(t_data *data);
int				_spawn_opps(t_data *data);
void			_opps_movements(t_data *data);
int				add_gengar_back(t_data *data, int (pos)[2]);
t_opps			*_which_gengar(t_data *data, int x, int y);
t_opps			*_get_last_gengar(t_data *data);
t_opps			*_create_gengar(int (pos)[2]);
void			free_gengar(t_data *data);
void			_destroy_gengar(t_opps *ops, t_data *data);
void			opps_collide(t_opps *ops, t_data *data);
void			key_collide(int x, int y, t_data *data);
void			exit_collide(t_data *data);
int				spawn_the_exit(t_data *data);
int				spawn_exit_keys(t_data *data);
int				flood_fill(char **map, char tofind, int posx, int posy);
int				_available_ncell(t_data *data, int pos[2]);
int				stay_away_fw(t_data *data, int x_y, int way, t_opps *ops);
#endif