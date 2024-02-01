#include <stdio.h>
#include <fcntl.h>
#include "cub3D.h"

int main(int argc, char **argv)
{
	t_map map;
	
	map_check(argc, argv, &map);
	return(0);
}