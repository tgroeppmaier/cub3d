#include "cub3D.h"

/*	Initializes the data, assets, and map structures */

void initialization(t_data* data, t_asset* assets, t_map* map)
{
	ft_memset(data, 0, sizeof(*data));
	ft_memset(assets, 0, sizeof(*assets));
	ft_memset(map, 0, sizeof(*map));
	data->map = map;
	data->assets = assets;
	// data->map->max_line_length = 2;
	// data->map->nbr_lines = 2;
}

int main(int argc, char **argv)
{
	t_data	data;
	t_asset	assets;
	t_map	map;

	initialization(&data, &assets, &map);
	check_argument(argc, argv);
	read_file(argv[1], &data);
	parse_file(&data);
	check_config(&data);
	create_map(&data);
	validate_map(&data);
	print_data(&data);
	free_file(&data);
	free_assets(&data);
	return 0;
}