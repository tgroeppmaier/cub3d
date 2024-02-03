#include "include/cub3D.h"

int main(int argc, char **argv)
{
	t_data	data;
	t_asset	assets;
	t_map	map;

	ft_memset(&assets, 0, sizeof(assets));
	ft_memset(&map, 0, sizeof(map));
	data.exit_loop = false;
	data.map = &map;
	data.assets = &assets;
		
	check_argument(argc, argv);
	read_file(argv[1], &data);
	parse_file(&data);
	return(0);
}