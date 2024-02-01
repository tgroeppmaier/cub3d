#include "cub3D.h"
#include <fcntl.h>

void	check_argument(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf("Error\n");
		printf("usage: ./cub3D mapname.cub\n");
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4)
	{
		printf("filename too short\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		ft_putstr("Error\n");
		ft_putstr("wrong filename! use .cub\n");
		exit(1);
	}
}

/*
	this function opens the file and reads it into buffer. 
	it reads up to buffer size - 1.
	A minimal valid map needs at least 17 bytes including line breaks. 
	if less are read, the map is invalid.
*/

void	open_map(char *path, t_map *map)
{
	int	fd;
	int	bytes_read;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_exit_read(1);
	bytes_read = read(fd, map->buffer, BUFFER_SIZE - 1);
	close(fd);
	if (bytes_read == -1)
		error_exit_read(2);
	if (bytes_read < MIN_FILE_SIZE)
		error_exit_read(3);
	if (bytes_read == BUFFER_SIZE - 1)
		error_exit_read(4);
	map->buffer[bytes_read] = '\0';
}

/* sets the dimensions x and y of the map (starting from 0) and also checks,
	if map is rectangular by comparing each line with the first line */

void	set_map_size(t_map *map)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(map->data[0]);
	while (map->data[i])
	{
		if (ft_strlen(map->data[i]) != len)
			error_exit_map(2, map);
		i++;
	}
	map->width = len - 1;
	map->height = i - 1;
}

void	set_player_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->data[i])
	{
		while (map->data[i][j])
		{
			if (map->data[i][j] == 'N' || map->data[i][j] == 'S' || map->data[i][j] == 'E' || map->data[i][j] == 'W')
			{
				map->player_x = j;
				map->player_y = i;
				map->player_direction = map->data[i][j];
				return;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

/* checks, if the map is surrounded by walls '1' */

static void	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (map->data[0][i])
	{
		if (map->data[0][i] != '1')
			error_exit_map(3, map);
		i++;
	}
	i = 0;
	while (map->data[map->height][i])
	{
		if (map->data[map->height][i] != '1')
			error_exit_map(3, map);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->data[i][0] != '1' || map->data[i][map->width] != '1')
			error_exit_map(3, map);
		i++;
	}
}

/* 	this function checks, if there is one player and no other 
	characters other than '0' '1' 'N' 'S' 'E' 'W' and '\n' 
	present.*/

static void	check_basics(t_map *map)
{
	int	i;

	i = 0;
	while (map->buffer[i])
	{
		if (map->buffer[i] == '1' || map->buffer[i] == '0'
			|| map->buffer[i] == '\n')
			;
		else if (map->buffer[i] == 'N')
			map->player_count++;			
		else if (map->buffer[i] == 'S')
			map->player_count++;
		else if (map->buffer[i] == 'E')
			map->player_count++;			
		else if (map->buffer[i] == 'W')
			map->player_count++;			
		else
			error_exit_read(5);
		i++;
	}
	if (map->player_count != 1)
		error_exit_read(6);
}

void	map_check(int argc, char **argv, t_map *map)
{
	check_argument(argc, argv);
	open_map(argv[1], map);
	check_basics(map);
	map->data = ft_split(map->buffer, '\n');
	set_map_size(map);
	set_player_pos(map);
	check_walls(map);
	map->data = ft_split(map->buffer, '\n');
}

