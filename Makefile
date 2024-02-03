CC=clang
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -pthread
LDFLAGS = -Llib -lmlx42 -ldl -lglfw -lm
ASANFLAGS = -fsanitize=address
NAME = cub3D 
SRC = main.c parse_map.c
OBJ = $(SRC:.c=.o)
HEADER = include/MLX42.h
LIBDIR = MLX42
LIBFT = src/libft

.PHONY: all clean fclean re lib asan libft

all: libft lib $(NAME)

asan: CFLAGS += -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: all

libft:
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a lib/

lib:
	cd $(LIBDIR) && cmake -B ../lib && cmake --build ../lib -j4

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 
	rm -f src/libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -rf lib/*

re: fclean all