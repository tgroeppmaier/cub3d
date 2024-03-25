#include "cub3D.h"

/*	Initializes the data, assets, and map structures */

void	initialization(t_data *data)
{
	ft_memset(data, 0, sizeof(*data));
	ft_memset(&(data->texinfo), 0, sizeof(data->texinfo));
	ft_memset(&(data->map), 0, sizeof(data->map));
	// data->map->width = 2;
	// data->map->height = 2;
}

int	main(int argc, char **argv)
{
	t_data data;

	initialization(&data);
	check_argument(argc, argv);
	read_file(argv[1], &data);
	parse_file(&data);
	check_config(&data);
	create_map(&data);
	validate_map(&data);
	
	init_mlx(&data);
	init_textures(&data);
	print_data(&data);
	free_file(&data);
	free_assets(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	printf("end reached\n");
	return (0);
}