NAME = cub3D

all: 
	make -C ./mandatory

bonus :
	make -C ./bonus

clean:
	make clean -C ./mandatory

clean_bonus:
	make clean -C ./bonus

fclean: clean
	make fclean -C ./mandatory

fclean_bonus : clean_bonus
	make fclean -C ./bonus

re : fclean all

re_bonus : fclean_bonus bonus

.PHONY: all clean fclean re bonus re_bonus re_bonus clean_bonus
