#ifndef CUB3D_H
# define CUB3D_H

# include "../src/libft/libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>

# define BLOCK_SIZE 64
# define BUFFER_SIZE 100
# define MIN_FILE_SIZE 17

typedef enum {
	ERR_USAGE,
	ERR_FILE_NOT_CUB,
	ERR_FILE_OPEN,
	ERR_IDENT,
	ERR_FILE_READ,
	ERR_FILE_SIZE,
	ERR_FILE_NOT_XPM,
	ERR_FILE_IS_DIR,
	ERR_FLOOR_CEILING,
	ERR_COLOR_FLOOR,
	ERR_COLOR_CEILING,
	ERR_INVALID_MAP,
	ERR_INV_LETTER,
	ERR_NUM_PLAYER,
	ERR_TEX_RGB_VAL,
	ERR_TEX_MISSING,
	ERR_TEX_INVALID,
	ERR_COLOR_MISSING,
	ERR_MAP_MISSING,
	ERR_MAP_TOO_SMALL,
	ERR_MAP_NO_WALLS,
	ERR_MAP_LAST,
	ERR_PLAYER_POS,
	ERR_PLAYER_DIR,
	ERR_MALLOC,
	ERR_MLX_START,
	ERR_MLX_WIN,
	ERR_MLX_IMG,
	ERR_COUNT // This is the total number of error codes
} ErrorCode;

typedef enum {
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_F,
	ID_C,
	ID_MAP,
	ID_UNKNOWN
} Identifier;

typedef struct s_color
{
	unsigned char 	red;
	unsigned char 	green;
	unsigned char 	blue;
	bool			color_ok;
}			t_color;

typedef struct s_map
{
	// int		width;
	// int		height;
	// int		player_x;
	// int		player_y;
	// int		player_count;
	// char		player_direction;
	bool		map_parsing;	// indicates, if map parsing has started
	int			max_line_length;
	int			nbr_lines;
	t_color 	ceiling;
	t_color 	floor;
	char		**map_arr;
	// char		**data;
}				t_map;

typedef struct s_asset
{
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
}			t_asset;

typedef struct s_data
{
	// void	*mxptr;
	// void	*mxwin;
	// void	*imgptr;
	// char	*addr;
	// int		bits_per_pixel;
	// int		line_length;
	// int		endian;
	// bool	exit_loop;
	char	*file;
	char	**file_by_line;
	t_asset	*assets;
	t_map	*map;
}			t_data;

/*			ft_split.c		*/
// size_t		ft_strlen(const char *s);
// char		**ft_split(char const *s, char c);

// /*          utils.c          */
// void		ft_putstr(char *str);
// int			ft_strncmp(const char *s1, const char *s2, size_t n);
// void		ft_putnbr(int n);
// void		*ft_memset(void *s, int c, size_t n);

/*          errors.c         */
// void		error_exit_read(int exit_code);
// void		free_map(t_map *map);
// void		error_exit_map(int exit_code, t_map *map);
// void		check_asset_error(t_data *image);
void		error_exit(t_data *data, ErrorCode code);
void 		free_assets(t_data *data);
void 		free_file(t_data *data);
void		print_error_exit(t_data *data, char *message);
void		free_array(char **array);

/* 			parse_file.c */
void		parse_file(t_data *data);
Identifier 	get_identifier(char *str);

/* 			read_file.c			*/
void		check_argument(int argc, char **argv);
void		read_file(char *path, t_data *data);
bool 		ft_isspace(int c);

/* 			parse_map.c			*/
void		check_invalid_char(char *line, t_data *data);
void		create_map(t_data *data);

/* 			debug.c		 		*/
void 		print_data(t_data *data);

/* 			checks.c	 		*/
void 		check_config(t_data *data);


#endif
