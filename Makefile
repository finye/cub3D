NAME = cub3D

SRC_DIR = srcs
SRCS = $(addprefix $(SRC_DIR)/, \
			clean.c \
			error.c \
			floor_ceiling.c \
			init.c \
			main.c \
			mlx_init.c \
			parse_file.c \
			parse_identifiers.c \
			player_init.c \
			player_movement.c \
			raycast_draw.c \
			raycast_textures.c \
			raycast_utils.c \
			store_map.c \
			validate_map.c \
			validate_texture.c)

OBJ_DIR =	objs
OBJS =		$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR =	./libft
LIBFT =		$(LIBFT_DIR)/libft.a

MLX_DIR =	./MLX42
MLX =		$(MLX_DIR)/build/libmlx42.a

CC =		cc
CFLAGS =	-Wall -Wextra -Werror -g
INCLUDES =	-I./libft/incl -I./incl -I./MLX42/include

RM =		rm -rf

GREEN =		\033[0;92m
BLUE =		\033[0;94m
END_COLOR =	\033[0m

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -lglfw -ldl -pthread -lm -o $(NAME)
	@echo "$(GREEN)cub3D compiled$(END_COLOR)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	@make -C $(MLX_DIR)/build -j4

all: $(LIBFT) $(MLX) $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(BLUE)Cleaned cub3D object files$(END_COLOR)"
	@$(RM) $(MLX_DIR)/build
	@echo "$(BLUE)Cleaned MLX42 build$(END_COLOR)"
	@make -C $(LIBFT_DIR) clean

fclean:
	@$(RM) $(NAME) $(OBJ_DIR)
	@echo "$(BLUE)Fully cleaned cub3D$(END_COLOR)"
	$(RM) $(MLX_DIR)
	@echo "$(BLUE)Fully cleaned MLX42$(END_COLOR)"
	@make -C $(LIBFT_DIR) fclean

re: fclean all

valgrind:
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all \
	--track-origins=yes --track-fds=yes --trace-children=yes -s \
	--suppressions=mlx_suppression.supp ./cub3D $(MAP);

.PHONY: all clean fclean re valgrind
