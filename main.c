#include "cub3D.h"

/*	Initializes the data, assets, and map structures */

void	initialization(t_data *data, t_texinfo *assets)
{
	ft_memset(data, 0, sizeof(*data));
	ft_memset(assets, 0, sizeof(*assets));
	ft_memset(&(data->map), 0, sizeof(data->map));
	data->assets = assets;
	// data->map->width = 2;
	// data->map->height = 2;
}

int	main(int argc, char **argv)
{
	t_data data;
	t_texinfo assets;

	initialization(&data, &assets);
	check_argument(argc, argv);
	read_file(argv[1], &data);
	parse_file(&data);
	check_config(&data);
	create_map(&data);
	validate_map(&data);
	print_data(&data);
	free_file(&data);
	free_assets(&data);
	return (0);
}