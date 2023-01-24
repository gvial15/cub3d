SRCS =	main.cpp

OBJS = $(SRCS:%cpp=%o)

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror 

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
