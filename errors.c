#include "cub3D.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void free_assets(t_data *data)
{
	free(data->assets->NO_path);
	free(data->assets->SO_path);
	free(data->assets->WE_path);
	free(data->assets->EA_path);
}

void free_file(t_data *data)
{
	int i;
	
	i = -1;
	free(data->file);
	data->file = NULL;
	while(data->file_by_line[++i])
	{
		free(data->file_by_line[i]);
		data->file_by_line[i] = NULL;
	}
	free(data->file_by_line);
	data->file_by_line = NULL;
}

void	print_error_exit(t_data *data, char *message)
{
	printf("%s\n", message);
	free_file(data);
	free_assets(data);
	exit(1);
}

void	error_exit(t_data *data, ErrorCode code)
{
	if(code == ERR_FILE_NOT_CUB)
		printf("file is not .cub\n");
	else if(code == ERR_FILE_READ)
		printf("error reading file\n");
	else if(code == ERR_FILE_IS_DIR)
		printf("is directory\n");
	else if(code == ERR_FILE_OPEN)
		printf("error opening file\n");
	else if(code == ERR_FILE_SIZE)
		printf("file too big\n");
	else if(code == ERR_IDENT)
		printf("Identifier error\n");
	else if(code == ERR_FLOOR_CEILING)
		printf("Floor / Ceiling error\n");
	free_file(data);
	free_assets(data);
	exit(1);
}

// void	error_exit_read(int exit_code)
// {
// 	if (exit_code == 1)
// 	{
// 		ft_putstr("Error\n");
// 		perror("open");
// 	}
// 	else if (exit_code == 2)
// 	{
// 		ft_putstr("Error\n");
// 		perror("read");
// 	}
// 	else if (exit_code == 3)
// 		ft_putstr("Error\nmap too small\n");
// 	else if (exit_code == 4)
// 		ft_putstr("Error\nmap too big\n");
// 	else if (exit_code == 5)
// 	{
// 		ft_putstr("Error\n");
// 		ft_putstr("invalid map, invalid characters\n");
// 	}
// 	else if (exit_code == 6)
// 		ft_putstr("Error\ninvalid map. wrong p count, e count or c count\n");
// 	exit(1);
// }

// void	free_map(t_map *map)
// {
// 	int		i;
// 	char	**data;

// 	data = map->data;
// 	i = 0;
// 	while (data[i])
// 	{
// 		free(data[i]);
// 		i++;
// 	}
// 	free(data);
// }

// void	error_exit_map(int exit_code, t_map *map)
// {
// 	if (exit_code == 2)
// 	{
// 		ft_putstr("Error\nmap is not rectangular\n");
// 		free_map(map);
// 		exit(1);
// 	}
// 	else if (exit_code == 3)
// 	{
// 		ft_putstr("Error\nmap not surrounded by walls\n");
// 		free_map(map);
// 		exit(1);
// 	}
// 	else if (exit_code == 4)
// 	{
// 		ft_putstr("Error\nno valid path\n");
// 		free_map(map);
// 		exit(1);
// 	}
// }

// void	check_asset_error(t_data *image)
// {
// 	if (!image->a->floor || !image->a->wall || !image->a->coll || !image->a->pl
// 		|| !image->a->pl_ex || !image->a->exit)
// 	{
// 		ft_putstr("Error\nAssets not loaded\n");
// 		free_map(image->map);
// 		// destroy_assets(image);
// 		// mlx_destroy_display(image->mxptr);
// 		free(image->mxptr);
// 		exit(1);
// 	}
// }
