#ifndef CUB3D_H
# define CUB3D_H

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
# define BUFFER_SIZE 2048
# define MIN_FILE_SIZE 17

typedef enum {
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_UNKNOWN
} Identifier;

Identifier get_identifier(char *str)
{
	if(ft_strncmp(str, "NO ", 3) == 0)
		return ID_NO;
	if(ft_strncmp(str, "SO ", 3) == 0)
		return ID_SO;
	if(ft_strncmp(str, "WE ", 3) == 0)
		return ID_WE;
	if(ft_strncmp(str, "EA ", 3) == 0)
		return ID_EA;
	return ID_UNKNOWN;
}

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
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);

/*          utils.c          */
void		ft_putstr(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putnbr(int n);
void		*ft_memset(void *s, int c, size_t n);

/*          errors.c         */
void		error_exit_read(int exit_code);
void		free_map(t_map *map);
void		error_exit_map(int exit_code, t_map *map);
void		check_asset_error(t_data *image);

/* 			parse_map.c */
void	check_argument(int argc, char **argv);
void	read_file(char *path, t_data *data);

void		parse_file(int argc, char **argv, t_data *data);


#endif
