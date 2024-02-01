#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define BLOCK_SIZE 64
# define BUFFER_SIZE 2048
# define MIN_FILE_SIZE 17

typedef struct s_map
{
	int		width;
	int		height;
	char	buffer[BUFFER_SIZE];
	int		player_x;
	int		player_y;
	int		player_count;
	char	player_direction;
	char	**data;
}			t_map;

typedef struct s_asset
{
	void	*wall;
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
	t_asset	*a;
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
void		map_check(int argc, char **argv, t_map *map);


#endif
