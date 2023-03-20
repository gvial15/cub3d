SRCS =	main.c display.c hook.c error.c \
		parse.c parse_texture.c parse_color.c parse_map.c parse_map2.c parse_texture2.c \
		print.c movement.c cast_rays.c texture.c \

OBJS = $(SRCS:%c=%o)

NAME = cub3d

# CFLAGS = -Wall -Wextra -Werror

CC = gcc

MAKELIB = cd lib/libft && make -s

LIB = lib/libft/libft.a

MAKELIBX = cd lib/mlx && make -s

LIBX = lib/mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKELIB)
	$(MAKELIBX)
	$(CC) $(OBJS) $(LIB) $(LIBX) -framework OpenGL -framework AppKit -o $(NAME)

clean:
	cd lib/libft && make clean -s
	$(RM) $(OBJS)

fclean: clean
	cd lib/libft && make fclean -s
	cd lib/mlx/ && make clean
	$(RM) $(NAME) -s

re: fclean all
