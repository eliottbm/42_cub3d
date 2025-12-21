# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 13:45:58 by ebengtss          #+#    #+#              #
#    Updated: 2024/12/20 16:54:18 by mtrullar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 			+=	--no-print-directory

NAME				=	cub3D
NAME_BONUS			=	cub3D_bonus

LIBFT				=	libft
LIBFT_A				=	libcustomft.a

LIBMLX				=	libmlx
LIBMLX_A			=	$(LIBMLX).a

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -I

LIBFT_DIR			=	libft
LIBMLX_DIR			=	minilibx-linux

SRCS_DIR			=	srcs/
PARSING_DIR			=	$(SRCS_DIR)parsing/
FREE_DIR			=	$(SRCS_DIR)free/
MLX_DIR				=	$(SRCS_DIR)mlx/
RAYCAST_DIR			=	$(SRCS_DIR)raycasting/
UTILS_DIR			=	$(SRCS_DIR)utils/
OBJS_DIR			=	objs/
INCS_DIR			=	incs

SRCS_BONUS_DIR		=	srcs_bonus/
PARSING_BONUS_DIR	=	$(SRCS_BONUS_DIR)parsing_bonus/
INITS_BONUS_DIR		=	$(SRCS_BONUS_DIR)inits_bonus/
FREE_BONUS_DIR		=	$(SRCS_BONUS_DIR)free_bonus/
MLX_BONUS_DIR		=	$(SRCS_BONUS_DIR)mlx_bonus/
RAYCAST_BONUS_DIR	=	$(SRCS_BONUS_DIR)raycasting_bonus/
UTILS_BONUS_DIR		=	$(SRCS_BONUS_DIR)utils_bonus/
DRAW_BONUS_DIR		=	$(SRCS_BONUS_DIR)draw_bonus/
MAP_BONUS_DIR		=	$(SRCS_BONUS_DIR)map_bonus/
OPPS_BONUS_DIR		=	$(SRCS_BONUS_DIR)opps_bonus/
OBJS_BONUS_DIR		=	objs_bonus/
INCS_BONUS_DIR		=	incs_bonus

SRCS_FILES			=	main.c			\
						parsing.c		\
						prs_textures.c	\
						prs_utils.c		\
						prs_map.c		\
						prs_map2.c		\
						free.c			\
						inputs.c		\
						raycast.c		\
						draw.c			\
						tools.c			\
						movements.c		\

SRCS_BONUS_FILES	=	main_bonus.c				spawn_keys_bonus.c			\
						data_inits_bonus.c			spawn_exit_bonus.c			\
						play_inits_bonus.c			opps_main_bonus.c			\
						enemy_sprite_bonus.c		opps_utils2_bonus.c			\
						imgs_inits_bonus.c			opps_utils_bonus.c			\
						imgs_inits_bonus2.c			opps_spawn_bonus.c			\
						imgs_inits_bonus3.c			opps_movements_bonus.c		\
						handle_maps.c				hp_draw_bonus.c				\
						handle_doors.c				mmap_vision_bonus.c			\
						parsing_bonus.c				mmap_player_bonus.c			\
						prs_textures_bonus.c		mmap_overlay_bonus.c		\
						prs_textures_bonus2.c		mmap_draw2_bonus.c			\
						prs_utils_bonus.c			mmap_draw_bonus.c			\
						prs_map_bonus.c				mmap_init_bonus.c			\
						prs_map_bonus2.c			lst_doors.c					\
						free_bonus.c				lst_maps.c					\
						free2_bonus.c				draw_previews_bonus.c		\
						raycast_bonus.c				draw_maps_bonus.c			\
						raycast_bonus2.c			draw_menu_bonus.c			\
						tools_bonus.c				draw_sprites_bonus.c		\
						tools2_bonus.c				draw_setup_bonus.c			\
						listen_mouse_bonus.c		draw_l2_bonus.c				\
						listen_mouse_maps_bonus.c	draw_world_bonus.c			\
						listen_inputs_bonus.c		draw_options_bonus.c		\
						player_moov_bonus.c			opps_movement_bis_bonus.c 	\

OBJS				=	$(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))
OBJS_BONUS			=	$(addprefix $(OBJS_BONUS_DIR), $(SRCS_BONUS_FILES:.c=.o))

DEF_COLOR			=	\033[0;39m
MAGENTA				=	\033[0;95m
GREEN				=	\033[0;92m
DEF_STYLE			=	\e[0m
BOLD_OPACITY		=	\e[1m\e[2m
RESET_LINE			=	\033[A\033[K

OBJSF				=	.objs_exists
OBJSF_BONUS			=	.objs_bonus_exists

all					:	$(NAME)
bonus				:	$(NAME_BONUS)

compile				=																					\
    $(CC) $(CFLAGS) $(INCS_DIR) -c $< -o $@;															\
	echo "$(RESET_LINE)$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)    compiling:    $(GREEN) $< $(DEF_COLOR)"	\

$(NAME)				:	$(LIBMLX_A) $(LIBFT_A) $(OBJS)
	@echo "$(RESET_LINE)$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	compiling:	$(GREEN) ✔ $(DEF_COLOR)"
	@$(CC) -o $(NAME) $(CFLAGS) $(INCS_DIR) $(OBJS) $(LIBFT_A) $(LIBMLX_A) -lX11 -lXext -lm
	@echo "$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	make:		$(GREEN) ✔ $(DEF_COLOR)"

$(NAME_BONUS)		:	$(LIBMLX_A) $(LIBFT_A) $(OBJS_BONUS)
	@echo "$(RESET_LINE)$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	compiling:	$(GREEN) ✔ $(DEF_COLOR)"
	@$(CC) -o $(NAME_BONUS) $(CFLAGS) $(INCS_BONUS_DIR) $(OBJS_BONUS) $(LIBFT_A) $(LIBMLX_A) -lX11 -lXext -lm
	@echo "$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	bonus:		$(GREEN) ✔ $(DEF_COLOR)"

$(LIBMLX_A)			:
	@make -C $(LIBMLX_DIR)
	@mv $(LIBMLX_DIR)/$(LIBMLX_A) ./

$(LIBFT_A)			:
	@make -C $(LIBFT_DIR)
	@mv $(LIBFT)/$(LIBFT_A) ./

$(OBJS_DIR)%.o		:	$(SRCS_DIR)%.c | $(OBJSF)
	@$(compile)

$(OBJS_DIR)%.o		:	$(PARSING_DIR)%.c | $(OBJSF)
	@$(compile)

$(OBJS_DIR)%.o		:	$(MLX_DIR)%.c | $(OBJSF)
	@$(compile)

$(OBJS_DIR)%.o		:	$(FREE_DIR)%.c | $(OBJSF)
	@$(compile)

$(OBJS_DIR)%.o		:	$(RAYCAST_DIR)%.c | $(OBJSF)
	@$(compile)

$(OBJS_DIR)%.o		:	$(UTILS_DIR)%.c | $(OBJSF)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(SRCS_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(PARSING_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(MLX_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(FREE_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(RAYCAST_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(UTILS_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(DRAW_BONUS_DIR)%.c | $(OBJSF_BONUS)
	$(compile)

$(OBJS_BONUS_DIR)%.o:	$(MAP_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(INITS_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJS_BONUS_DIR)%.o:	$(OPPS_BONUS_DIR)%.c | $(OBJSF_BONUS)
	@$(compile)

$(OBJSF)			:
	@echo "$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	nothing to do"
	@mkdir -p $(OBJS_DIR)

$(OBJSF_BONUS)		:
	@echo "$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	nothing to do"
	@mkdir -p $(OBJS_BONUS_DIR)

clean				:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_BONUS_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)
	@rm -f $(LIBFT_A)
	@rm -f $(LIBMLX_A)
	@echo "$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	clean:		$(GREEN) ✔ $(DEF_COLOR)"

fclean				:	clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "$(BOLD_OPACITY)[ CUB3D ]$(DEF_STYLE)	fclean:		$(GREEN) ✔ $(DEF_COLOR)"

re					:	fclean all

reb					:	fclean bonus

.PHONY				:	all bonus clean fclean re reb