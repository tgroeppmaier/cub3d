#include "include/cub3D.h"

void print_color(t_color color) 
{
	printf("Red: %u, Green: %u, Blue: %u\n", color.red, color.green, color.blue);
	printf("color_ok: %d\n", color.color_ok);
}

void print_map(t_map *map) 
{
	int i = 0;
	char **tmp;
	
	tmp = map->map_arr;
	if(!tmp)
	{
		printf("map array == NULL\n");
		exit(1);
	}
	printf("Floor color: ");
	print_color(map->floor);
	printf("Ceiling color: ");
	print_color(map->ceiling);
	printf("max line length = %d\n", map->width);
	printf("number of lines: %d\n", map->height);
	printf("player count: %d\n", map->p_count);
	printf("player x: %d\n", map->player_x);
	printf("player y: %d\n", map->player_y);
	printf("player direction: %c\n", map->player_direction);
	// while(*tmp)
	// {
	// 	printf("%s\n", *tmp);
	// 	tmp++;
	// }
	while(map->map_arr[i])
	{
		printf("%s\n", map->map_arr[i]);
		i++;
	}
	// while(map->map_start[i])
	// {
	// 	printf("%s\n", map->map_start[i]);
	// 	i++;
	// }
	free_array(map->map_arr);
}

void print_asset(t_asset *asset) 
{
	printf("NO path: %s\n", asset->NO_path);
	printf("SO path: %s\n", asset->SO_path);
	printf("WE path: %s\n", asset->WE_path);
	printf("EA path: %s\n", asset->EA_path);
}

void print_data(t_data *data)
{
	// printf("File: %s\n", data->file);
	print_asset(data->assets);
	print_map(data->map);
	// char **temp = data->file_by_line;
	// while(*temp)
	// {
	// 	printf("%s\n", *temp);
	// 	temp++;
	// }
}