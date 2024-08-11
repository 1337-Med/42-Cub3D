
SRC =	./sources/parser/parser.c \
		./sources/cub3d.c \
		./sources/raycasting/utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I ./includes -I ./super_libft

NAME = cub3d

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./super_libft
	$(CC) $(CFLAGS) ./super_libft/libft.a ./mlx/build/libglfw3.a ./mlx/build/libmlx42.a -o $(NAME) $(OBJ)

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
