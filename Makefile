CC=clang
CFLAGS = -Iinclude -pthread
LDFLAGS = -Linclude -lmlx42 -ldl -lglfw -lm
NAME = cube3D 
SRC = cube3D.c
OBJ = $(SRC:.c=.o)
HEADER = include/MLX42.h

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all