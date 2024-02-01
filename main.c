#include <stdio.h>
#include <fcntl.h>
#include "cub3D.h"
#include <string.h>

int main(int argc, char **argv)
{
	t_data	image;
	t_asset	assets;
	t_map	map;

	memset(&assets, 0, sizeof(assets));
	memset(&map, 0, sizeof(map));
	image.exit_loop = false;
	image.map = &map;
	image.a = &assets;
	
	map_check(argc, argv, &map);
	printf("%s", map.buffer);
	printf("Player direction: %c\n", map.player_direction);
	return(0);
}