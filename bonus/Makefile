
SRC =	./sources/parser/parser_bonus.c ./sources/parser/parser_utils_bonus.c ./sources/parser/parser_utils1_bonus.c  ./sources/parser/texture_parsing_bonus.c ./sources/parser/map_parsing_bonus.c\
		./sources/cub3d_bonus.c \
		./sources/raycasting/utils_bonus.c \
		./sources/raycasting/raycaster_bonus.c \
		./sources/rander_texture/rander_texture_bonus.c \
		./sources/raycasting/horiz_bonus.c \
		./sources/raycasting/vertical_bonus.c \
		./sources/raycasting/movement_bonus.c \
		./sources/raycasting/create_rays_bonus.c \
		./sources/raycasting/cast_rays_bonus.c \
		./sources/raycasting/move_condition_bonus.c \
		./sources/raycasting/render_rec_bonus.c \
		./sources/raycasting/mouse_rotation_bonus.c \
		./sources/raycasting/mini_map_bonus.c \
		./sources/raycasting/render_map_bonus.c \
		./sources/raycasting/render_player_bonus.c \
		./sources/raycasting/ft_hook_bonus.c \

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror  -I ./includes -I ../super_libft -O3 

NAME = ../cub3D_bonus

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../super_libft
	$(CC) $(CFLAGS) ../super_libft/libft.a ../MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)  $(OBJ)

%.o: %.c ./includes/cub3d_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ../super_libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ../super_libft
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
