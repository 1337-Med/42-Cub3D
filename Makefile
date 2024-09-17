
SRC =	./sources/parser/parser.c ./sources/parser/parser_utils.c ./sources/parser/parser_utils1.c  ./sources/parser/texture_parsing.c ./sources/parser/map_parsing.c\
		./sources/cub3d.c \
		./sources/raycasting/utils.c \
		./sources/raycasting/raycaster.c \
		./sources/rander_texture/rander_texture.c \
		./sources/raycasting/horiz.c \
		./sources/raycasting/vertical.c \
		./sources/raycasting/movement.c \
		./sources/raycasting/create_rays.c \
		./sources/raycasting/cast_rays.c \
		./sources/raycasting/move_condition.c \
		./sources/raycasting/render_rec.c \
		./sources/raycasting/mouse_rotation.c \
		./sources/raycasting/mini_map.c \
		./sources/raycasting/render_map.c \
		./sources/raycasting/render_player.c \
		./sources/raycasting/ft_hook.c \

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -I ./includes -I ./super_libft -O3 #-fsanitize=address -g

NAME = cub3D

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./super_libft
	$(CC) $(CFLAGS) ./super_libft/libft.a ./MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)  $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./super_libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./super_libft
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
