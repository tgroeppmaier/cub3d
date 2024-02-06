#include "include/cub3D.h"

int main(int argc, char **argv)
{
	t_data	data;
	t_asset	assets;
	t_map	map;


	ft_memset(&data, 0, sizeof(data));
	ft_memset(&assets, 0, sizeof(assets));
	ft_memset(&map, 0, sizeof(map));
	data.map = &map;
	data.assets = &assets;
		
	check_argument(argc, argv);
	read_file(argv[1], &data);
	// printf("%s\n", data.buffer);
	parse_file(&data);
	print_data(&data);
	free_file(&data);
	free_assets(&data);
	return(0);
}