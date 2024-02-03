#include <stdio.h>
#include <fcntl.h>
#include "cub3D.h"
#include <string.h>

int main(int argc, char **argv)
{
	t_data	data;
	t_asset	assets;
	t_map	map;

	memset(&assets, 0, sizeof(assets));
	memset(&map, 0, sizeof(map));
	data.exit_loop = false;
	data.map = &map;
	data.assets = &assets;
		
	check_argument(argc, argv);
	read_file(argv[1], &data);
	parse_file(argc, argv, &data);
	return(0);
}