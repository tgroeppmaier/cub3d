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
# define BUFFER_SIZE 20480
# define MIN_FILE_SIZE 17

typedef enum {
	ERR_USAGE,
	ERR_FILE_NOT_CUB,
	ERR_FILE_OPEN,
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
	ID_UNKNOWN
} Identifier;



typedef struct s_map
{
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		player_count;
	char	player_direction;
	char	**data;
}			t_map;

typedef struct s_asset
{
	void	*NO_path;
	void	*SO_path;
	void	*WE_path;
	void	*EA_path;
	void	*floor;
	void	*coll;
	void	*exit;
	void	*pl;
	void	*pl_ex;
}			t_asset;

typedef struct s_data
{
	void	*mxptr;
	void	*mxwin;
	void	*imgptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	bool	exit_loop;
	char	buffer[BUFFER_SIZE];
	char	**file;
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
void		error_exit(ErrorCode code);

/* 			parse_map.c */
void		check_argument(int argc, char **argv);
void		read_file(char *path, t_data *data);

void		parse_file(t_data *data);


#endif
