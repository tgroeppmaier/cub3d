CC=clang
CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread
LDFLAGS = -Llib -lmlx42 -ldl -lglfw -lm
NAME = cube3D 
SRC = cube3D.c
OBJ = $(SRC:.c=.o)
HEADER = include/MLX42.h
LIBDIR = MLX42

.PHONY: all clean fclean re lib

all: lib $(NAME)

lib:
	cd $(LIBDIR) && cmake -B ../lib && cmake --build ../lib -j4

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
	rm -rf lib/*

re: fclean all