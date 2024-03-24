CC=clang
CFLAGS = -Wall -Wextra -Werror -g -Iinclude #-pthread
LIBS = -Llib -lmlx -lft -lX11 -lXext
ASANFLAGS = -fsanitize=address
NAME = cub3D 
SRC = main.c parse_file.c parse_map.c errors.c debug.c parse_file_2.c read_file.c map_check.c \
init_textures.c
OBJ = $(SRC:.c=.o)
HEADER = include/mlx.h
LIBDIR = mlx
LIBFT = src/libft

.PHONY: all clean fclean re lib asan libft

all: libft lib $(NAME)

asan: CFLAGS += -fsanitize=address
asan: LIBS += -fsanitize=address
asan: all

libft:
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a lib/

lib:
	cd $(LIBDIR) && make
	cp $(LIBDIR)/libmlx.a lib/

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 
	rm -f src/libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -rf lib/*

re: fclean all
