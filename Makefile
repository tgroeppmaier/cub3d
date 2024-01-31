CC=clang
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -pthread
LDFLAGS = -Llib -lmlx42 -ldl -lglfw -lm
ASANFLAGS = -fsanitize=address
NAME = cube3D 
SRC = cube3D.c
OBJ = $(SRC:.c=.o)
HEADER = include/MLX42.h
LIBDIR = MLX42

.PHONY: all clean fclean re lib asan

all: lib $(NAME)

asan: CFLAGS += -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: all

lib:
	cd $(LIBDIR) && cmake -B ../lib && cmake --build ../lib -j4

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
	rm -rf lib/*

re: fclean all