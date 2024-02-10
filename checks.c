#include "cub3D.h"

void check_config(t_data *data)
{
	if(!data->assets->NO_path || !data->assets->SO_path || !data->assets->WE_path || !data->assets->EA_path)
		print_error_exit(data, "asset path error");
	if(!data->map->ceiling.color_ok || !data->map->floor.color_ok)
		print_error_exit(data, "color error");
}


