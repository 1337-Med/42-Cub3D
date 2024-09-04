
SRC =	./sources/parser/parser.c ./sources/parser/parser_utils.c  ./sources/parser/texture_parsing.c ./sources/parser/map_parsing.c\
		./sources/cub3d.c \
		./sources/raycasting/utils.c \
		./sources/raycasting/raycaster.c \
		./sources/rander_texture/rander_texture.c \
		./sources/raycasting/horiz.c \
		./sources/raycasting/vertical.c

OBJ = $(SRC:.c=.o)
# GLFW = $(shell brew --prefix glfw)

# DEPS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"$(GLFW)/lib" $(MLX42)
CFLAGS = -Wall -Wextra -I ./includes -I ./super_libft #-O3 #-fsanitize=address -g# -O3

NAME = cub3d

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
