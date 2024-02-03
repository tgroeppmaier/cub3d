#include "include/cub3D.h"

int main(int argc, char **argv)
{
	t_data	data = {0};
	t_asset	assets = {0};
	t_map	map = {0};

	// ft_memset(&assets, 0, sizeof(assets));
	// ft_memset(&map, 0, sizeof(map));
	data.exit_loop = false;
	data.map = &map;
	data.assets = &assets;
		
	check_argument(argc, argv);
	read_file(argv[1], &data);
	// printf("%s\n", data.buffer);
	parse_file(&data);
	return(0);
}